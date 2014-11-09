#include "optutil.h"

using namespace std;
using namespace comm;

bool OptUtil::parse_args(int argc, char** argv, std::map<char, std::string>& opt_arg_map)
{
	if (argc<2 || argv==NULL)
	{
		return false;
	}

	for (int i = 0; i< argc; i+=2)
	{
		string opt = argv[i];

		if (opt.length() != 2 || opt[0] != '-')
		{
			return false;
		}

		char c_opt = opt[1];

		if (i+1 >= argc)
		{
			return false;
		}

		string arg = argv[i+1];
		opt_arg_map[c_opt] = arg;
	}

	return true;
}
