#include "fileutil.h"
#include "exputil.h"

 #include <string.h>
#include <fcntl.h>
#include<sys/stat.h>
#if defined(WIN32)
#include <io.h>
#endif

using namespace std;
using namespace comm;

bool FileUtil::open_ifstream(std::ifstream& stm, const std::string& fileName)
{
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale loc = locale::global(locale(""));
#endif	
	stm.open(fileName.c_str());
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale::global(loc);
#endif

	return stm.is_open();
}

bool FileUtil::open_ifstream(std::ifstream& stm, const std::string& fileName,
#if defined(WIN32) || defined(_WIN32_WCE)
std::ios_base::open_mode mode)
#else
std::_Ios_Openmode mode)
#endif
{
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale loc = locale::global(locale(""));
#endif
	stm.open(fileName.c_str(), mode);
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale::global(loc);
#endif
	return stm.is_open();
}

bool FileUtil::open_ofstream(std::ofstream& stm, const std::string& fileName)
{
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale loc = locale::global(locale(""));
#endif
	stm.open(fileName.c_str());
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale::global(loc);
#endif
	return stm.is_open();
}

bool FileUtil::open_ofstream(std::ofstream& stm, const std::string& fileName,
#if defined(WIN32) || defined(_WIN32_WCE) || defined(__SYMBIAN32__)
std::ios_base::open_mode mode)
#else
std::_Ios_Openmode mode)
#endif
{
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale loc = locale::global(locale(""));
#endif
	stm.open(fileName.c_str(), mode);
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale::global(loc);
#endif
	return stm.is_open();
}

bool FileUtil::file_exist(const std::string& fileName)
{
	ifstream stm;
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale loc = locale::global(locale(""));
#endif	
	stm.open(fileName.c_str());
#if defined(WIN32) && !defined(_WIN32_WCE)
	locale::global(loc);
#endif
	bool exist = stm.is_open();
	stm.close();
	return exist;
}

std::string FileUtil::getBaseName(const std::string& filename)
{
    int index = filename.find_last_of(".");
    if (index == string::npos)
        return filename;
    
    return filename.substr(0, index);
}

std::string FileUtil::getExtName(const std::string& filename)
{
    int index = filename.find_last_of(".");
    if (index == string::npos)
        return "";
    else
        index += 1;
    
    return filename.substr(index, filename.length()-index);
}

int FileUtil::getFileSize(const std::string& filename)
{
	struct stat st;
	memset (&st, 0, sizeof(struct stat));
	if (stat (filename.c_str(), &st) == 0 )
		return st.st_size;
	return -1;
}

void FileUtil::deleteFile(const std::string& filename)
{
	remove(filename.c_str());
}
