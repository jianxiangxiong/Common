#include "mutex.h"
#include "logger.h"

using namespace std;

namespace comm
{

DT_mutex* DT_CreateMutex()
{
	DT_mutex* mutex = new DT_mutex;

#ifdef _WIN32
	/* On SMP systems, a non-zero spin count generally helps performance */
	InitializeCriticalSectionAndSpinCount(&mutex->mutex, 2000);
	//InitializeCriticalSection(&mutex->mutex);
#else
	if( pthread_mutex_init( &mutex->mutex, NULL ) != 0 )
	{
		comm_printf("pthread_mutex_init error\n");   
		free(mutex);
		return NULL;
	}
#endif
	
	return mutex;
}

void DT_DestroyMutex(DT_mutex* mutex)
{
	if( mutex == NULL )
		return;

#ifdef _WIN32
	DeleteCriticalSection(&mutex->mutex );
#else
	if(pthread_mutex_destroy(mutex->mutex) != 0 )
		comm_printf("Attempt to destroy locked mutex!");
#endif

	delete mutex; 
}

int DT_Mutex_lock_real( DT_mutex* mutex, const char* file, int line)
{
	if( mutex == NULL )
		return -1;

#ifdef _WIN32
	EnterCriticalSection(&mutex->mutex);
#else
	if(pthread_mutex_lock( mutex->mutex) != 0)
	{
		comm_printf("%Mutex failed ! (Called from %s:%d)", file, line);
		return -1;
	}
#endif
	return 0;
}

int DT_Mutex_unlock_real( DT_mutex* mutex, const char* file, int line)
{
	if( mutex == NULL )
		return -1;

#ifdef _WIN32
	LeaveCriticalSection(&mutex->mutex);
#else
	if( pthread_mutex_unlock( mutex->mutex ) != 0)
	{
		comm_printf("Mutex unlock failed! ( Called from %s:%d)", file, line);
		return -1;
	}
#endif

	return 0;
}

}
