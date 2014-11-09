#ifndef LOGGER_H__
#define LOGGER_H__

#include <string>

namespace comm
{

#define DT_LOGPRINT			"DT_LOGPRINT"
#define DT_LOGAPPEND		"DT_LOGAPPEND"
#define DT_LOGFLUSH			"DT_LOGFLUSH"
#define DT_LOGMULTI			"DT_LOGMULTI"
#define DT_LOGMAXSIZE		"DT_LOGMAXSIZE"
#define DT_LOGPRINTIPC		"DT_LOGPRINTIPC"

class Logger
{
public:
	Logger(const std::string& fileName);
	Logger(const std::string& fileName, bool output, bool append);
	Logger(const std::string& fileName, bool output, bool append, bool flush, int max_size);
    ~Logger();
	void log(const std::string& str);
	void logFmt(const char* fmt, ...);
	FILE* getHandle();

    static bool GetLogPrint();
    static bool GetLogMulti();
    static bool GetLogAppend();

protected: 
	//��Ա���������������ӣ���LOGGER��mysock, mydns, myroute����Ϊ�������ݣ����õ���ƣ�������취ȥ��ż��)
    std::string     m_fileName;
    FILE*           m_filePtr;
	bool            m_output;
    char*           m_szMsg;

private:
	void init(const std::string& fileName, bool output, bool append, bool flush, int max_size);
	Logger(const Logger& other);
	Logger& operator=(const Logger&);
};

std::string get_default_logpath();
void comm_printf(char* fmt, ...);
}

#endif
