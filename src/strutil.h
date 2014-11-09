#ifndef STRUTIL_H__
#define STRUTIL_H__

#include <string>
#include <vector>
#include "platinc.h"

namespace comm
{
#if defined(__LINUX__) || defined ANDROID
	#define CP_OEMCP	1  
#endif

typedef std::vector<std::string> StringArray;

class StrUtil
{
public:
	//ȥ����ͷ�����ո�
	static void trim(std::string& src);
	static void ltrim(std::string& src);
	static void rtrim(std::string& src);

	//�����滻
	static bool hasContain(const std::string& src, const char* subStr);
	static void replace(std::string &src, const char* oldStr, const char *newStr);

	//�ϲ����
	static std::string combine(const StringArray& srcs, char spilt);
	static void spilt(const std::string& src, char spilt, StringArray& strs, bool needTrim=true);
	static void spilt(const std::string& src, const char* spilt, StringArray& strs, bool needTrim=true);

	//�жϿ�ͷ���β
	static bool beginWith(const std::string& src, const std::string& beginStr);
	static bool endWith(const std::string& src, const std::string& endStr);
	static void removeBeginStr(std::string& src, const std::string& begStr);
	static void removeEndStr(std::string& src, const std::string& endStr);

	//ת��
	static std::string Int2Str(int val);
	static std::string Int642Str(INT64 val);
	static std::string Dbl2Str(double val);
	static int Str2Int(const std::string& val);
	static INT64 Str2Int64(const std::string& val);
	static double Str2Dbl(const std::string& val);

#if defined(WIN32) || defined(_WIN32_WCE)
	static std::string Unicode2Mbcs(const std::wstring& inWStr, int code_page=CP_OEMCP);
	static std::wstring Mbcs2Unicode(const std::string& inStr, int code_page=CP_OEMCP);
	static std::string Local2Utf8(const std::string& inStr);
#endif
	
	//�ж��Ƿ�ȫ����ֵ
	static bool isNumeric(const std::string& val);	

    //ת����Сд
    static void toUpper(std::string& src);
    static void toLower(std::string& src);

private:
	StrUtil();
};

} //namespace

#endif	//STRUTIL_H__
