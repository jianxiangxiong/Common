#ifndef OPT_UTIL_H__
#define OPT_UTIL_H__

#include <string>
#include <map>

namespace comm
{
	class OptUtil
	{
	public:
		//argv: must with head with "-X", and argc/2=0
		static bool parse_args(int argc, char** argv, std::map<char, std::string>& opt_arg_map);
	};
}

#endif

