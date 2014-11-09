#include "thread.h"
#include "logger.h"

namespace comm
{

/* This is the function called to run a thread */
#ifdef _WIN32
static DWORD WINAPI run_thread(void *arg)
#else
static void* run_thread(void *arg)
#endif
{
	DT_Thread* thread = (DT_Thread*)(arg);
	(thread->start_routine)( thread->arg);
	return 0;
}

DT_Thread* DT_CreateThread(int (*routine)(void*), void *arg)
{
	DT_Thread* thd = new DT_Thread();
	thd->arg = arg;
	thd->start_routine = routine;

#ifdef _WIN32
	thd->handle = CreateThread(NULL, 0, run_thread, thd, 0, NULL);
	if( thd->handle == NULL )
	{
		comm_printf("Create Thread Failed!\n");
		delete thd;
		return NULL;
	}
#else
	pthread_attr_t type;

	/* Set the thread attributes */
	if ( pthread_attr_init(&type) != 0 ) {
		comm_printf("Couldn't initialize pthread attributes\n");
		delete thd;
		return NULL;
	}
	pthread_attr_setdetachstate(&type, PTHREAD_CREATE_JOINABLE);
	
	/* Create the thread and go! */
	if ( pthread_create(&thread->handle, &type, run_thread, thd) != 0 ) {
		comm_printf("Not enough resources to create thread\n");
		delete thd;
		return NULL;
	}
#endif
	return thd;
}

unsigned int DT_GetThreadID(void)
{
#ifdef _WIN32
	return (int)GetCurrentThreadId();
#else
	return (int)pthread_self();
#endif
}

void DT_WaitThread(DT_Thread *thread, int *status)
{
#ifdef _WIN32
	WaitForSingleObject(thread->handle, INFINITE);
	CloseHandle(thread->handle);
#else
	pthread_join(thread->handle, status);
#endif
	delete thread;
}

}
