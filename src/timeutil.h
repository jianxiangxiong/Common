#ifndef TIME_UTIL_H__
#define TIME_UTIL_H__

#include "platinc.h"
#include <string>

namespace comm
{
/**
* 时间相关函数 
*/
class TimeUtil
{
public:
	static double diffTimevalMS(timeval t1, timeval t2);
	static UINT64 convertTimevalToMS(const timeval &tv);
	static timeval convertMSToTimeval(UINT64 ms);
	static int gettimeofday(struct timeval* tp, int* tz);
	static std::string getymd_hns();
	static std::string getymd_hns_std();
	static std::string getymd_hnsm();
	static std::string getymd_hnsm_std();
	static std::string gethnsm_std();
};

}

#endif
