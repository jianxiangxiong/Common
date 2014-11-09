#include "common.h"
using namespace std;
using namespace comm;

int main(int argc, char** argv)
{
	//CIniFile iniFile;
	//bool result = iniFile.load(PathUtil::GetExePathA() + "aa.ini");
	//if (result)
	//{

	//	char buff[200];
	//	iniFile.GetValue("test", "name", "", buff, sizeof(buff));
	//	int age = iniFile.GetValueInt("test", "age", 0);
	//	double high = iniFile.GetValueReal("test", "high", 0.);
	//	printf("%s %d %lf\n", buff, age, high);

	//	iniFile.SetValue("test", "name", "jianxx2");
	//	iniFile.SetValueInt("test", "age", 31);
	//	iniFile.SetValueReal("test", "high", 18.0);
	//}

	//int size = FileUtil::getFileSize("E:\\Project\\datatests\\third\\Common\\fileutil.cpp");

//	FileUtil::deleteFile("E:\\Project\\datatests\\datatests_win32\\Release\\log\\ftp_up_qos.csv");

	Logger logger("E:\\Project\\datatests\\datatests_win32\\Release\\log\\ftp_up_receiver.log", 
		true, true, true, 300);

	logger.log("hello!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!111");

	return 0;
}
