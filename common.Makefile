


ARCH=x64Linux2.6gcc4.4.5
CC=g++
CFLAGS = -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64 -std=gnu++1y -Wno-deprecated -DBOOST_DATE_TIME_POSIX_TIME_STD_CONFIG
LDFLAGS = -m64 -lstdc++ -static-libgcc
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt

MongoLib = -lmongoclient -L../MongoClientLib/lib
BOOSTLIBS = -lboost_system -lboost_date_time
