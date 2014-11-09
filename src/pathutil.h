#ifndef PATH_UTIL_H__
#define PATH_UTIL_H__

#include <string>

namespace comm
{

/**
* 路径相关函数  
*/
class PathUtil
{
public:
	static std::string GetExePathA();
	static std::string GetIniPath();
    static std::string GetLogPath();
	static std::wstring GetExePathW();

	static bool	PathExist(const std::string& path);
	static bool PathCreate(const std::string& path);

    static std::string getPathOfFullFilename(std::string& fullFileName);
    static std::string getFilenameOfFullFilename(std::string& fullFileName);
};

}

#endif
