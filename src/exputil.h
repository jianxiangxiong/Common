#ifndef EXPUTIL_H__
#define EXPUTIL_H__

#include <exception>
#include <string>

namespace comm
{
#define ERRCODE_FILE_NOTEXIST			9001
#define ERRCODE_FILE_OPENFAILED			9002
#define ERRCODE_FILE_CREATEFAILED		9003
#define ERRCODE_FAILED_LOAD_LIBRARY		9004
#define ERRCODE_UNKNOWN					9005

/**
* 自定义异常
*/
class MyException
#if defined(WIN32) || defined(_WIN32_WCE) || defined(__SYMBIAN32__)
: public std::exception
#endif
{
public:
	MyException(int err_code, const std::string& err_descr, int err_code2=0) 
#if defined(WIN32) || defined(_WIN32_WCE)
	:std::exception(err_descr.c_str())
#else
	:m_what(err_descr)
#endif
	{
		m_errcode = err_code;
		m_errcode2 = err_code2;
	}

#if defined(WIN32) || defined(_WIN32_WCE)

#else
	virtual const char* what() const
	{
		return m_what.c_str();
	}
#endif

	int GetErrCode() const
	{
		return m_errcode;
	}

	int GetErrCode2() const 
	{
		return m_errcode2;
	}

protected:
	int m_errcode;
	int m_errcode2; //小分类代码

#if defined(WIN32) || defined(_WIN32_WCE)
	
#else
	std::string m_what;
#endif
};

}

#endif //EXPUTIL_H__
