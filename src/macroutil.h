#ifndef MACRO_UTIL_H__
#define MACRO_UTIL_H__

namespace comm
{
//should not use.
//the thread in linux will not realse if not wait
#define WAIT_THREAD(runThd, runFlag) \
{ \
	if ((runFlag) && runThd!=NULL) \
	{ \
		SDL_WaitThread(runThd, NULL); \
		runThd= NULL; \
	} \
} \

#define DELAY_COND(delay_ms, runFlag) \
{ \
	if (runFlag) \
	{ \
		int start_t = SDL_GetTicks(); \
		while(true) \
		{ \
			int now_t = SDL_GetTicks(); \
			if (!(runFlag) || (now_t-start_t)>=delay_ms) \
			{ \
				break; \
			} \
			SDL_Delay(10); \
		} \
	} \
} \

#define DT_DELAY_COND(delay_ms, runFlag) \
{ \
	if (runFlag) \
	{ \
		int start_t = DT_GetTicks(); \
		while(true) \
		{ \
			int now_t = DT_GetTicks(); \
			if (!(runFlag) || (now_t-start_t)>=delay_ms) \
			{ \
				break; \
			} \
			DT_Delay(10); \
		} \
	} \
} \

#define SAFE_DELETE(obj) \
{ \
	if(obj != NULL) \
	{ \
		delete obj; \
		obj = NULL; \
	} \
} \

} //namespace comm

#endif

