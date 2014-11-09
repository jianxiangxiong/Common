#ifndef FILE_UTIL_H__
#define FILE_UTIL_H__

#include <fstream>

namespace comm
{
class FileUtil
{
public:
	static bool open_ifstream(std::ifstream& stm, const std::string& fileName);
	static bool open_ifstream(std::ifstream& stm, const std::string& fileName,
#if defined(WIN32) || defined(_WIN32_WCE)
std::ios_base::open_mode mode);
#else
std::_Ios_Openmode mode);
#endif
	static bool open_ofstream(std::ofstream& stm, const std::string& fileName);
	static bool open_ofstream(std::ofstream& stm, const std::string& fileName, 
#if defined(WIN32) || defined(_WIN32_WCE)
std::ios_base::open_mode mode);
#else
std::_Ios_Openmode mode);
#endif
	static bool file_exist(const std::string& fileName);
	static std::string getBaseName(const std::string& filename);
	static std::string getExtName(const std::string& filename);
	static int getFileSize(const std::string& filename);
	static void deleteFile(const std::string& filename);
};
}

#endif
