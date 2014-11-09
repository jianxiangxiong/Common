#include "iniutil.h"
#include <string.h>
#include <stdlib.h>

using namespace comm;


std::string IniUtil::getStrFromIni(CIniFile& iniFile, const char* sec, const char* key, const char* defVal)
{
	char item_value[1024];
	memset(item_value, 0x00, sizeof(item_value));
	iniFile.GetValue(sec, key, defVal, item_value, sizeof(item_value));
	return item_value;
}

int IniUtil::getIntFromIni(CIniFile& iniFile, const char* sec, const char* key, int defVal, int minVal, int maxVal)
{
	int retVal = iniFile.GetValueInt(sec, key, defVal);
	if (retVal<minVal || retVal>maxVal)
	{
		retVal = defVal;
	}
	return retVal;
}

bool IniUtil::getBoolFromIni(CIniFile& iniFile, const char* sec, const char* key, int defVal)
{
	int retVal = iniFile.GetValueInt(sec, key, defVal);
	return retVal!=0;
}

double IniUtil::getDoubleFromIni(CIniFile& iniFile, const char* sec, const char* key, double defVal, double minVal, double maxVal)
{
    double retVal = iniFile.GetValueReal(sec, key, defVal);
    
    if (retVal<minVal || retVal>maxVal)
        retVal = defVal;
    
    return retVal;
}
