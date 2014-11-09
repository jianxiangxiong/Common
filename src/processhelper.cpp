#include "processhelper.h"
#include "strutil.h"

#ifdef _WIN32
#include <TlHelp32.h>
#else
#endif

using namespace std;
using namespace comm;

ProcessHelper::ProcessHelper(Logger* logger)
{
	m_logger = logger;
}

#ifdef _WIN32
int ProcessHelper::GetProcessCount(const char* processName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 lppe;
	BOOL found;
	int count = 0;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	lppe.dwSize = sizeof(PROCESSENTRY32);
	found=Process32First(hSnapshot,&lppe);

	while(found)
	{
		string exe_name = StrUtil::Unicode2Mbcs(lppe.szExeFile);
		if(exe_name == processName)
		{
			count++;
		}
		found = Process32Next(hSnapshot,&lppe);
	}
	CloseHandle(hSnapshot);
	return count;
}

void ProcessHelper::KillProcessByName(const char* processName)
{
	HANDLE hSnapshot;
	PROCESSENTRY32 lppe;
	BOOL found;
	hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	lppe.dwSize = sizeof(PROCESSENTRY32);
	found=Process32First(hSnapshot,&lppe);
	if (!found)
	{
		CloseHandle(hSnapshot);
		return;
	}

	while(found)
	{
		string exe_name = StrUtil::Unicode2Mbcs(lppe.szExeFile);
		if(exe_name == processName)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, lppe.th32ProcessID);
			if (hProcess)
			{
				if (TerminateProcess(hProcess,0))
					m_logger->logFmt("TerminateProcess %s success", processName);
				else
					m_logger->logFmt("TerminateProcess %s Failed", processName);
				CloseHandle(hProcess);
			}
		}
		found = Process32Next(hSnapshot,&lppe);
	}
	CloseHandle(hSnapshot);
}

void ProcessHelper::KillProcessById(int pid)
{
	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, pid);
	if (hProcess)
	{
		if (TerminateProcess(hProcess,0))
			m_logger->logFmt("TerminateProcess %d success", pid);
		else
			m_logger->logFmt("TerminateProcess %d Failed", pid);
		CloseHandle(hProcess);
	}	
}
#else
int ProcessHelper::GetProcessCount(const char* processName)
{
	return 0;
}
void ProcessHelper::KillProcessById(int pid)
{

}
void ProcessHelper::KillProcessByName(const char* processName)
{

}
#endif