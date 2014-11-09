#ifndef SYS_UTIL_H__
#define SYS_UTIL_H__

#include <string>

namespace comm
{

class SysUtil
{
public:
	//�õ�������(-��ͷ)
	//arg_0��ԭ���ݸ�����WIN����,argc_o=0 argv_o=ULL
	static void getCmdLineArgs(int argc_i, char** argv_i, int& argc_r, char**& argv_r);
	static void releaseCmdLineArgs(int argc_r, char** argv_r);
	static int getRandom(int n);

    static bool setEnv(const char* key, const char* value);
    static std::string getEnv(const char* key);
	static bool getEnvBool(const char* key, bool defValue);
	static int getEnvInt(const char* key, int defValue);
	static double getEnvDbl(const char* key, double defValue);
};

}

#endif
