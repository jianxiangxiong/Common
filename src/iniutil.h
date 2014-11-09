#ifndef INI_UTIL_H__
#define INI_UTIL_H__
#include "inifile.h"

namespace comm
{

class IniUtil
{
public:
	static std::string getStrFromIni(CIniFile& iniFile, const char* sec, const char* key, const char* defVal);
	static int getIntFromIni(CIniFile& iniFile, const char* sec, const char* key, int defVal, int minVal, int maxVal);
	static bool getBoolFromIni(CIniFile& iniFile, const char* sec, const char* key, int defVal);
    static double getDoubleFromIni(CIniFile& iniFile, const char* sec, const char* key, double defVal, double minVal, double maxVal);
};

}

#endif
