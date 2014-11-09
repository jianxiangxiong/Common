#include "timeutil.h"
#include <time.h>
#include <string.h>

#if defined(WIN32) && !defined(_WIN32_WCE)
#include <sys/timeb.h>
#elif defined(__SYMBIAN32__)
#include <e32std.h>
#elif defined(__LINUX__) || defined(ANDROID)
#include <sys/timeb.h>
#endif

using namespace std;
using namespace comm;

double TimeUtil::diffTimevalMS(timeval t1, timeval t2)
{
	return (t1.tv_sec - t2.tv_sec) * 1000.0 + (t1.tv_usec - t2.tv_usec) / 1000.0;
}

UINT64 TimeUtil::convertTimevalToMS(const timeval &tv) {
	return ((UINT64)tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

timeval TimeUtil::convertMSToTimeval(UINT64 ms)
{
	timeval tv;
	tv.tv_sec = (long)(ms / 1000);
	tv.tv_usec = (long)((ms % 1000) * 1000);
	return tv;
}

std::string TimeUtil::getymd_hns()
{
	char ymd_nhs[100];
	memset(ymd_nhs, 0x00, sizeof(ymd_nhs));

#if defined(_WIN32_WCE)
	SYSTEMTIME systm;
	GetLocalTime( &systm );
	sprintf(ymd_nhs, "%04d%02d%02d_%02d%02d%02d",
		systm.wYear, systm.wMonth,
		systm.wDay, systm.wHour, systm.wMinute, systm.wSecond);
#else
	struct tm *local;
	time_t t;
	t=time(NULL);
	local=localtime(&t);

	sprintf(ymd_nhs, "%04d%02d%02d_%02d%02d%02d",
		1900+local->tm_year, 1+local->tm_mon,
		local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
#endif
	return string(ymd_nhs);
}

std::string TimeUtil::getymd_hns_std()
{
	char ymd_nhs[100];
	memset(ymd_nhs, 0x00, sizeof(ymd_nhs));

#if defined(_WIN32_WCE)
	SYSTEMTIME systm;
	GetLocalTime( &systm );
	sprintf(ymd_nhs, "%04d/%02d/%02d %02d:%02d:%02d",
		systm.wYear, systm.wMonth,
		systm.wDay, systm.wHour, systm.wMinute, systm.wSecond);
#else
	struct tm *local;
	time_t t;
	t=time(NULL);
	local=localtime(&t);

	sprintf(ymd_nhs, "%04d/%02d/%02d %02d:%02d:%02d",
		1900+local->tm_year, 1+local->tm_mon,
		local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec);
#endif
	return string(ymd_nhs);
}

std::string TimeUtil::getymd_hnsm()
{
	const char* time_fmt = "%04d%02d%02d_%02d%02d%02d_%03d";

	char szHnsm[100];
	memset(szHnsm, 0x00, sizeof(szHnsm));

#if defined(_WIN32_WCE)
	SYSTEMTIME systm;
	GetLocalTime(&systm);
	sprintf(szHnsm, time_fmt,
		systm.wYear, systm.wMonth,
		systm.wDay, systm.wHour, systm.wMinute, systm.wSecond, systm.wMilliseconds);
#else
	struct tm *local;
	struct timeb tp;

	ftime(&tp);
	local=localtime(&(tp.time));

	sprintf(szHnsm, time_fmt,
		1900+local->tm_year, 1+local->tm_mon,
		local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, tp.millitm);
#endif

	return string(szHnsm);
}

std::string TimeUtil::getymd_hnsm_std()
{
	const char* time_fmt = "%04d/%02d/%02d %02d:%02d:%02d.%03d";

	char szHnsm[100];
	memset(szHnsm, 0x00, sizeof(szHnsm));

#if defined(_WIN32_WCE)
	SYSTEMTIME systm;
	GetLocalTime(&systm);
	sprintf(szHnsm, time_fmt,
		systm.wYear, systm.wMonth,
		systm.wDay, systm.wHour, systm.wMinute, systm.wSecond, systm.wMilliseconds);
#else
	struct tm *local;
	struct timeb tp;

	ftime(&tp);
	local=localtime(&(tp.time));

	sprintf(szHnsm, time_fmt,
		1900+local->tm_year, 1+local->tm_mon,
		local->tm_mday, local->tm_hour, local->tm_min, local->tm_sec, tp.millitm);
#endif

	return string(szHnsm);
}

int TimeUtil::gettimeofday(struct timeval* tp, int* tz)
{
#if defined(WIN32) && defined(_WIN32_WCE)
	/* FILETIME of Jan 1 1970 00:00:00. */
	static const unsigned __int64 epoch = 116444736000000000LL;

	FILETIME    file_time;
	SYSTEMTIME  system_time;
	ULARGE_INTEGER ularge;

	GetSystemTime(&system_time);
	SystemTimeToFileTime(&system_time, &file_time);
	ularge.LowPart = file_time.dwLowDateTime;
	ularge.HighPart = file_time.dwHighDateTime;

	tp->tv_sec = (long) ((ularge.QuadPart - epoch) / 10000000L);
	tp->tv_usec = (long) (system_time.wMilliseconds * 1000);

#elif defined(WIN32) && !defined(_WIN32_WCE)
	static LARGE_INTEGER tickFrequency, epochOffset;

	// For our first call, use "ftime()", so that we get a time with a proper epoch.
	// For subsequent calls, use "QueryPerformanceCount()", because it's more fine-grain.
	static bool isFirstCall = true;

	LARGE_INTEGER tickNow;
	QueryPerformanceCounter(&tickNow);

	if (isFirstCall) 
	{
		struct timeb tb;
		ftime(&tb);
		tp->tv_sec = (long)tb.time;
		tp->tv_usec = 1000 * tb.millitm;

		// Also get our counter frequency:
		QueryPerformanceFrequency(&tickFrequency);

		// And compute an offset to add to subsequent counter times, so we get a proper epoch:
		epochOffset.QuadPart
			= tb.time*tickFrequency.QuadPart + (tb.millitm*tickFrequency.QuadPart)/1000 - tickNow.QuadPart;

		isFirstCall = false; // for next time
	}
	else
	{
		// Adjust our counter time so that we get a proper epoch:
		tickNow.QuadPart += epochOffset.QuadPart;

		tp->tv_sec = (long) (tickNow.QuadPart / tickFrequency.QuadPart);
		tp->tv_usec = (long) (((tickNow.QuadPart % tickFrequency.QuadPart) * 1000000L) / tickFrequency.QuadPart);
	}
#else
	return ::gettimeofday(tp, NULL);
#endif
	return 0;
}

std::string TimeUtil::gethnsm_std()
{
	const char* time_fmt = "%02d:%02d:%02d.%03d";

	char szHnsm[100];
	memset(szHnsm, 0x00, sizeof(szHnsm));

#if defined(_WIN32_WCE)
	SYSTEMTIME systm;
	GetLocalTime(&systm);
	sprintf(szHnsm, time_fmt,
		systm.wHour, systm.wMinute, systm.wSecond, systm.wMilliseconds);

#else
	struct tm *local;
	struct timeb tp;

	ftime(&tp);
	local=localtime(&(tp.time));

	sprintf(szHnsm, time_fmt,
		local->tm_hour, local->tm_min, local->tm_sec, tp.millitm);
#endif

	return string(szHnsm);
}

