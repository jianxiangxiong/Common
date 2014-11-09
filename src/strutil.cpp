#include "strutil.h"

#include <sstream>
#include <iterator>
#include <cassert>
#include <iomanip>
#include <string.h>
#include <stdlib.h>

#if defined(WIN32) || defined(_WIN32_WCE)
#include <Windows.h>
#endif

#if 0//defined ANDROID
size_t mbstowcs(wchar_t *pwcs, const char *s, size_t n)
{
	if (pwcs == NULL)
		return strlen(s);
	return mbsrtowcs(pwcs, &s, n, NULL);
}

size_t wcstombs(char *s, const wchar_t *pwcs, size_t n)
{

	return wcsrtombs(s, &pwcs, n, NULL);
}
#endif

using namespace std;
using namespace comm;

void StrUtil::trim(std::string& src)
{
	if (src.empty())
	{
		return;
	}

	ltrim(src);
	rtrim(src);
}

void StrUtil::ltrim(std::string& src)
{
	if (src.empty())
	{
		return;
	}

	size_t index = src.find_first_not_of(" \t\r\n");
	if (index == string::npos) {
		src = "";
	}
	else {
		src = src.substr(index);
	}
}

void StrUtil::rtrim(std::string& src)
{
	if (src.empty())
	{
		return;
	}

	size_t index = src.find_last_not_of(" \t\r\n");
	if (index == string::npos) {
		src = "";
	}
	else {
		src = src.substr(0, index+1);
	}
}

bool StrUtil::hasContain(const std::string& src, const char* subStr)
{
	if (subStr==NULL || strcmp(subStr, "")==0)
	{
		return false;
	}

	return src.find(subStr) != string::npos;
}

void StrUtil::replace(std::string &src, const char* oldStr, const char *newStr)
{
	if (src.empty())
	{
		return;
	}

	if (oldStr==NULL || strcmp(oldStr, "")==0 || newStr==NULL)
	{
		return;
	}

	int index = (int)src.find(oldStr);   
	while(index != string::npos)
	{   
		src.replace(index, strlen(oldStr), newStr);   
		index = (int)src.find(oldStr, index+strlen(newStr));   
	}
}

std::string StrUtil::combine(const StringArray& srcs, char spilt)
{
	if(srcs.empty())
	{
		return "";
	}

	string str_spilt = string(1, spilt);
	ostringstream oss;	
	ostream_iterator<string> os_iter(oss, str_spilt.c_str());
	copy(srcs.begin(), srcs.end(), os_iter);

	string str = oss.str();
	removeEndStr(str, str_spilt);

	return str;
}

void StrUtil::spilt(const std::string& src, char spilt, StringArray& strs, bool needTrim /*=true*/)
{
	if (src.empty()) {
		return; 
	}

	istringstream iss(src);
	while (!iss.eof())
	{
		string str;
		getline(iss, str, spilt);
		if (needTrim)
		{
			trim(str);
		}
		strs.push_back(str);
	}	

}

void StrUtil::spilt(const std::string& src, const char* spilt, StringArray& strs, bool needTrim /*=true*/)
{
	int pos = 0;
	int last_pos = 0;
	string elem;
	int spilt_len = strlen(spilt);

	while( (pos=src.find(spilt, last_pos)) != -1 )
	{
		elem = src.substr(last_pos, pos-last_pos);
		if (needTrim)
		{
			trim(elem);
		}
		strs.push_back(elem);
		last_pos = pos + spilt_len;
	}

	//last elem
	elem = src.substr(last_pos);
	if (needTrim)
	{
		trim(elem);
	}
	strs.push_back(elem);
}

bool StrUtil::beginWith(const std::string& src, const std::string& beginStr)
{
	if (src.empty() || beginStr.empty())
	{
		return false;
	}

	if (src.length() <beginStr.length())
	{
		return false;
	}

	if (src.substr(0, beginStr.length()) == beginStr)
	{
		return true;
	}

	return false;
}

bool StrUtil::endWith(const std::string& src, const std::string& endStr)
{
	if (src.empty() || endStr.empty())
	{
		return false;
	}

	if (src.length() < endStr.length())
	{
		return false;
	}
	
	if (src.substr(src.length() - endStr.length())==endStr)
	{
		return true;
	}
	
	return false;
}

void  StrUtil::removeBeginStr(std::string& src, const std::string& begStr)
{
	if (beginWith(src, begStr))
	{
		src = src.substr(begStr.length());
	}
}

void StrUtil::removeEndStr(std::string& src, const std::string& endStr)
{
	if (endWith(src, endStr))
	{
		src = src.erase(src.length() - endStr.length());
	}
}

std::string StrUtil::Int2Str(int val)
{
	char temp[100];
	sprintf(temp, "%d", val);
	return temp;
}

std::string StrUtil::Int642Str(INT64 val)
{
	char temp[100];
	sprintf(temp, INT64OUTFORMAT, val);
	return temp;
}

std::string StrUtil::Dbl2Str(double val)
{
	char temp[100];
	sprintf(temp, "%.2f", val);
	return temp;
}

int StrUtil::Str2Int(const std::string& val)
{
	return atoi(val.c_str());
}

INT64 StrUtil::Str2Int64(const std::string& val)
{
#if defined(WIN32) || defined(_WIN32_WCE)
	return _atoi64(val.c_str());
#else
	return atoll(val.c_str());
#endif
}

double StrUtil::Str2Dbl(const std::string& val)
{
	return atof(val.c_str());
}

bool StrUtil::isNumeric(const std::string& val)
{
	if (val.empty())
	{
		return false;
	}

	for (int i=0; i<(int)val.size(); i++)
	{
		#if defined(ANDROID)
		if(val[i]<'0' && val[i]>'9')
		#else
		if (!isdigit(val[i]))
		#endif		
		{
			return false;
		}
	}
	return true;
}

void StrUtil::toUpper(std::string& src)
{
    int i=0, len=src.length();

    for (i=0; i<len; i++)
    {
        if ((src[i] >= 'a') && (src[i] <= 'z'))
            src[i] -= 32;
    }
}

void StrUtil::toLower(std::string& src)
{
    int i=0, len=src.length();

    for (i=0; i<len; i++)
    {
        if ((src[i] >= 'A') && (src[i] <= 'Z'))
            src[i] += 32;
    }
}

#if defined(WIN32) || defined(_WIN32_WCE)
std::string StrUtil::Unicode2Mbcs(const std::wstring& inWStr, int code_page)
{
	int length = WideCharToMultiByte (code_page, NULL, inWStr.c_str(), -1, NULL, 0, NULL, FALSE);
	char* pStr = new char[length + 1];
	ZeroMemory(pStr, sizeof(char) * (length+1));

	WideCharToMultiByte (code_page, NULL, inWStr.c_str(), -1, pStr, 
			length, NULL, FALSE);

	string str = pStr;
	delete[] pStr;
	return str;
}

std::wstring StrUtil::Mbcs2Unicode(const std::string& inStr, int code_page)
{
	int length = MultiByteToWideChar(code_page, NULL, inStr.c_str(), -1,  NULL, 0);
	wchar_t* pWideStr = new wchar_t[length + 1];
	ZeroMemory(pWideStr, sizeof(wchar_t) * (length + 1));
	
	MultiByteToWideChar(code_page, NULL, inStr.c_str(), -1, pWideStr, length);
	
	wstring wideStr = pWideStr;
	delete[] pWideStr;
	return wideStr;
}

std::string StrUtil::Local2Utf8(const std::string& inStr)
{
	std::wstring str_unicode = StrUtil::Mbcs2Unicode(inStr);	
	return StrUtil::Unicode2Mbcs(str_unicode, CP_UTF8);
}
#endif
