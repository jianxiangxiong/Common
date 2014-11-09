#include "platinc.h"
#include "logger.h"
#include "timeutil.h"
#include "sysutil.h"
#include "fileutil.h"
#include "pathutil.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>
#if defined(WIN32) && !defined(_WIN32_WCE)
#include <sys/timeb.h>
#endif

using namespace comm;
using namespace std;

#define MSG_MAX_SIZE (5*1024)
#define LOGFILE_MAX_SIZE (10*1024*1024)
static bool m_flushAtOnce = true; //can't add member in class, reason describe in header file

Logger::Logger(const std::string& fileName)
{
	bool output = GetLogPrint();
	bool append = GetLogAppend();
	bool flush = SysUtil::getEnvBool(DT_LOGFLUSH, true);
	int max_size = SysUtil::getEnvInt(DT_LOGMAXSIZE, LOGFILE_MAX_SIZE);
	
	init(fileName, output, append, flush, max_size);
}

Logger::Logger(const std::string& fileName, bool output, bool append)
{
	bool flush = SysUtil::getEnvBool(DT_LOGFLUSH, true);
	int max_size = SysUtil::getEnvInt(DT_LOGMAXSIZE, 0);
	init(fileName, output, append, flush, max_size);
}

Logger::Logger(const std::string& fileName, bool output, bool append, bool flush, int max_size)
{
	init(fileName, output, append, flush, max_size);
}

void Logger::init(const std::string& fileName, bool output, bool append, bool flush, int max_size)
{
	m_filePtr = NULL;
	m_szMsg = NULL;
	m_output = output;
	if (!m_output)
	{
		return;
	}

	m_flushAtOnce = flush;
	m_fileName = fileName;

	if (max_size > 0)
	{
		if(FileUtil::getFileSize(m_fileName) >= max_size)
		{
			FileUtil::deleteFile(m_fileName.c_str());
		}
	}

	if (append)
	{
		m_filePtr = fopen(m_fileName.c_str(), "at");
	}
	else
	{
		m_filePtr = fopen(m_fileName.c_str(), "wt");
	}	

	if (!m_filePtr)
	{
		m_output = false;
		return;
	}

	m_szMsg = (char*)malloc(MSG_MAX_SIZE);;
	if (m_szMsg == NULL)
	{
		m_output = false;
		return;
	}
}

Logger::~Logger()
{
    if (m_filePtr)
    {
        fclose(m_filePtr);
        m_filePtr = NULL;
    }

    if (m_szMsg)
    {
        free(m_szMsg);
        m_szMsg = NULL;
    }
}

FILE* Logger::getHandle()
{
	return m_filePtr;
}

void Logger::log(const std::string& str)
{
	if (!m_output)
	{
		return;
	}

    fprintf(m_filePtr, "%s %s\n", TimeUtil::getymd_hnsm_std().c_str(), str.c_str());
	if (m_flushAtOnce)
	{
		fflush(m_filePtr);
	}
}

void Logger::logFmt(const char* fmt, ...)
{
	if (!m_output)
	{
		return;
	}

	memset(m_szMsg, 0x00, MSG_MAX_SIZE);

	va_list argList;
	va_start(argList, fmt);
	cvsnprintf(m_szMsg, MSG_MAX_SIZE -1 , fmt, argList);
	va_end(argList);

    fprintf(m_filePtr, "%s %s\n", TimeUtil::getymd_hnsm_std().c_str(), m_szMsg);
	if (m_flushAtOnce)
	{
		fflush(m_filePtr);
	}
}

bool Logger::GetLogPrint()
{
	return SysUtil::getEnvBool(DT_LOGPRINT, true);
}

bool Logger::GetLogMulti()
{
	return SysUtil::getEnvBool(DT_LOGMULTI, true);
}

bool Logger::GetLogAppend()
{
	return SysUtil::getEnvBool(DT_LOGAPPEND, true);
}

namespace comm
{
	std::string get_default_logpath()
	{
		string log_path;
	#if defined(WIN32)
		log_path = "c:\\ipc2\\";
	#elif defined(__IPHONEOS__)
		log_path = "/var/root/log/";
	#elif defined(__RCU__) || defined(__SCOUT__)
		log_path = "/dos/log/datatests/";
		if (FileUtil::file_exist(log_path + "flush.txt"))	
	#elif defined(ANDROID)
		log_path = "/mnt/sdcard/ipc2/";
	#else
		log_path = "./log/";
	#endif
		return log_path;
	}

	#define COMM_LOG_FILE "dtcomm.log"
	static Logger* g_logger = NULL;

	void comm_printf(char* fmt, ...)
	{
		if(g_logger == NULL)	
		{
			string log_path = get_default_logpath();

			if (!PathUtil::PathExist(log_path))
			{
				PathUtil::PathCreate(log_path);
			}

			g_logger = new Logger(log_path + COMM_LOG_FILE);
		}

		char szMsg[MSG_MAX_SIZE];
		va_list argList;
		va_start(argList, fmt);
		cvsnprintf(szMsg, MSG_MAX_SIZE -1 , fmt, argList);
		va_end(argList);

		g_logger->log(szMsg);
	}
}
