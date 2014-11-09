#include "timerutil.h"

#ifdef WIN32
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace comm
{
#ifdef _WIN32
	#define TIME_WRAP_VALUE	(~(DWORD)0)
	static DWORD start = 0;
#else
	static struct timeval start;
#endif

	static void start_ticks()
	{
#ifdef _WIN32
		start = GetTickCount();
#else
		gettimeofday(&start, NULL);
#endif
	}

	//ms
	unsigned int DT_GetTicks()
	{
		if (start == 0)
		{
			start_ticks();
			return 0;
		}

#ifdef _WIN32
		DWORD now, ticks;
		now = GetTickCount();

		if (now < start) {
		 ticks = (TIME_WRAP_VALUE - start) + now;
		} else {
		 ticks = (now - start);
		}
#else
		unsigned int ticks;
		struct timeval now;

		gettimeofday(&now, NULL);
		ticks =	(now.tv_sec - start.tv_sec) * 1000 + (now.tv_usec -
			start.tv_usec) / 1000;
#endif
		return (ticks);
	}

	void DT_Delay(unsigned int ms)
	{
#ifdef _WIN32
		Sleep(ms);
#else
		int was_error;
		struct timeval tv;
		unsigned int then, now, elapsed;
		then = DT_GetTicks();

		do {
			errno = 0;
			/* Calculate the time interval left (in case of interrupt) */
			now = DT_GetTicks();
			elapsed = (now - then);
			then = now;
			if (elapsed >= ms) {
				break;
			}
			ms -= elapsed;
			tv.tv_sec = ms / 1000;
			tv.tv_usec = (ms % 1000) * 1000;

			was_error = select(0, NULL, NULL, NULL, &tv);
		 } while (was_error && (errno == EINTR));
#endif
	}
}
