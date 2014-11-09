#ifndef COMM_THREAD_H__
#define COMM_THREAD_H__

#ifdef WIN32
#include <Windows.h>
#else
#include <pthread.h>
#endif

namespace comm
{
	/* This is the system-independent thread info structure */
	struct DT_Thread {
#ifdef _WIN32
		HANDLE handle;
#else
		pthread_t handle;
#endif
		int (*start_routine)(void*);
		void* arg;  
	};

	/** Create a thread */
	DT_Thread* DT_CreateThread(int (*routine)(void*), void *arg);

	/** Get the 32-bit thread identifier for the current thread */
	unsigned int DT_GetThreadID(void);

	/** Wait for a thread to finish.
	 *  The return code for the thread function is placed in the area
	 *  pointed to by 'status', if 'status' is not NULL.
	 *  will free thread when finish
	 */
	void DT_WaitThread(DT_Thread *thread, int *status);
}

#endif
