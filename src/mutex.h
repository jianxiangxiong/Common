#ifndef COMM_DT_Mutex_H__
#define COMM_DT_Mutex_H__

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

namespace comm
{
#ifdef _WIN32
	struct DT_mutex
	{
		CRITICAL_SECTION mutex;
	};
#else
	struct DT_mutex
	{
		pthread_mutex_t mutex;
	};
#endif

	DT_mutex* DT_CreateMutex();

	void DT_DestroyMutex(DT_mutex* mutex);

#define DT_LockMutex(m) DT_Mutex_lock_real( m, __FILE__, __LINE__)

	int DT_Mutex_lock_real( DT_mutex* mutex, const char* file, int line);

#define DT_UnlockMutex(m) DT_Mutex_unlock_real( m, __FILE__, __LINE__)

	int DT_Mutex_unlock_real( DT_mutex* mutex, const char* file, int line);
}

#endif //COMM_DT_Mutex_H__
