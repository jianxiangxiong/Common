DEVELOPER=/Developer/Platforms/iPhoneOS.platform/Developer
IPHONESDK=$(DEVELOPER)/SDKs/iPhoneOS5.0.sdk
CC=$(DEVELOPER)/usr/bin/arm-apple-darwin10-llvm-g++-4.2

INCPATH += -I./
INCPATH += -I$(IPHONESDK)/usr/include/c++/4.2.1/
INCPATH += -I$(IPHONESDK)/usr/include/c++/4.2.1/armv7-apple-darwin10/

DFLAGS = -isysroot $(IPHONESDK) $(INCPATH) -D__LINUX__ -D__IPHONEOS__ -fvisibility=hidden
AR = $(DEVELOPER)/usr/bin/ar

OBJS = fileutil.o inifile.o iniutil.o logger.o pathutil.o strutil.o sysutil.o timeutil.o optutil.o

all:$(OBJS)
	$(AR) -cr libCommon.a $(OBJS)

fileutil.o:../fileutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

inifile.o:../inifile.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

iniutil.o:../iniutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

logger.o:../logger.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

pathutil.o:../pathutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

strutil.o:../strutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

sysutil.o:../sysutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

timeutil.o:../timeutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

optutil.o:../optutil.cpp
	$(CC) $(DFLAGS) -c $^ -o $@

test:../test.cpp
	$(CC) $(DFLAGS) -L./ -lCommon $^ -o $@

clean:
	rm *.o libCommon.a
