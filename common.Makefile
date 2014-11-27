


ARCH=x64Linux3.xgcc4.6.3
CC=g++
CFLAGS = -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64 -std=gnu++1y -Wno-deprecated
LDFLAGS = -m64 -static-libgcc
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt

MongoLib = -lmongoclient -L../MongoClientLib/lib
BOOSTLIBS = -lboost_system -lboost_date_time