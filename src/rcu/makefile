objects = fileutil.o inifile.o iniutil.o logger.o pathutil.o strutil.o sysutil.o timeutil.o optutil.o

CC=g++
AR=ar
DFLAGS=-D__LINUX__ -D__RCU__ -fvisibility=hidden 

all:$(objects)
	$(AR) cr libCommon.a $(objects)

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

clean:
	rm libCommon.a $(objects)

