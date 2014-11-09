#ifndef PROCESS_HELPER_H__
#define PROCESS_HELPER_H__

#include "logger.h"

namespace comm
{

class ProcessHelper
{
public:
	ProcessHelper(Logger* logger);

	int GetProcessCount(const char* processName);
	void KillProcessById(int pid);
	void KillProcessByName(const char* processName);

private:
	comm::Logger* m_logger;
};

}

#endif
