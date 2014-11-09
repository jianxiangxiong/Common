#ifndef PLAT_INC_H__
#define PLAT_INC_H__

#if defined(WIN32) || defined(_WIN32_WCE)
	#include <WinSock2.h>
	#include <Windows.h>
	#define csnprintf _snprintf
	#define cvsnprintf _vsnprintf
	#define INT64OUTFORMAT "%I64d"
	#define UINT64OUTFORMAT "%I64u"
#else
	#include <sys/socket.h>
	#include <sys/select.h>
	#include <sys/time.h>
	#include <sys/types.h>
	#include <sys/wait.h>
	#include <netinet/in.h>
	#include <arpa/inet.h>
	#include <netdb.h>
	#include <fcntl.h>
	#include <unistd.h>
	#include <errno.h>
    #include <net/if.h>
    #include <string.h>
	#include <stdio.h>

	#define csnprintf snprintf
	#define cvsnprintf vsnprintf
	typedef long long INT64;
	typedef unsigned long long	UINT64;
	typedef unsigned char BYTE;
	typedef unsigned int  DWORD;
	#define INT64OUTFORMAT "%lld"
	#define UINT64OUTFORMAT "%llu"
#endif

#if defined(ANDROID) //ANDROID Makefile中定义__LINUX__无效
	#define __LINUX__	1
#endif

#endif
