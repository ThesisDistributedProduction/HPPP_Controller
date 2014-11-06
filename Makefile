###################################################################################
##           (c) Copyright, Real-Time Innovations, All rights reserved.          ##
##                                                                               ##
## Permission to modify and use for internal purposes with RTI software granted. ##
##    This software is provided "as is", without warranty, express or implied.   ##
##                                                                               ##
###################################################################################

# Note:
# - To use this Makefile, you must have the 'NDDSHOME' environment variable
#   set to the location of RTI Connext.
# 
# - You need to invoke the make command from the root directory of this example.
#
# - To enable debugging information, set the Makefile variable 'DEBUG' to '1'.
# Example:
#   make -f make/Makefile.x64Linux3.xgcc4.6.3 DEBUG=1


# Defines required Make variables. They will be used in the Makefile.common
# to define the rules to define the build process for this application.
ARCH=x64Linux3.xgcc4.6.3
#-std=gnu++11
#-std=gnu++1y
CC=g++
CFLAGS = -DRTI_UNIX -DRTI_LINUX -DRTI_64BIT -m64 -std=gnu++1y -Wno-deprecated	
LDFLAGS = -m64 -static-libgcc
SYSLIBS = -ldl -lnsl -lm -lpthread -lrt -lmongoclient
BOOSTLIBS = -lboost_system -lboost_date_time
#SHAREDLIB = 1

ifeq ($(NDDSHOME), )
all:
	@echo "***************************************************************"
	@echo "The environment variable 'NDDSHOME' is not set!"
	@echo "To use this makefile you need to set NDDSHOME to the directory"
	@echo "where you have RTI Connext installed."
	@echo "***************************************************************"
	@false
endif


ifeq ($(DEBUG),1)
	COMPILER_FLAGS += -g -O0
	ifeq ($(SHAREDLIB),1)
		NDDSLIBS = -lnddscppd -lnddscd -lnddscored
	else
		NDDSLIBS = -lnddscppzd -lnddsczd -lnddscorezd
	endif
else
	COMPILER_FLAGS += -O2
	ifeq ($(SHAREDLIB),1)
		NDDSLIBS = -lnddscpp -lnddsc -lnddscore
	else
		NDDSLIBS = -lnddscppz -lnddscz -lnddscorez
	endif
endif


LIBS = -L$(NDDSHOME)/lib/$(ARCH) -L$(HOME)/mongo-client-install/lib $(NDDSLIBS) $(BOOSTLIBS) $(SYSLIBS)

#INC=-I/usr/informix/incl/c++ /opt/informix/incl/public
INCLUDES=-I$(HOME)/mongo-client-install/include \
	-I./Common \
	-I$(NDDSHOME)/include/ \
	-I$(NDDSHOME)/include/ndds

SOURCES_CPP = $(wildcard Common/*.cpp) \
					$(wildcard Common/Turbine/*.cpp) \
					$(wildcard DecentralizedParkPilot/*.cpp)
					
SOURCES_CXX = $(wildcard Common/*.cxx)

EXECUTABLE    = DecentralizedParkPilot_exe
SOURCES_CPP_NODIR = $(notdir $(SOURCES_CPP))
SOURCES_CXX_NODIR = $(notdir $(SOURCES_CXX))
SOURCES = $(SOURCES_CPP) #$(SOURCES_CXX)
OBJECTS	= $(SOURCES_CPP_NODIR:%.cpp=objs/%.o) $(SOURCES_CXX_NODIR:%.cxx=objs/%.o)

#$(info )
#$(info [${SOURCES}])
#$(info )
#$(info [${OBJECTS}])
#$(info )

###############################################################################
# Build Rules
###############################################################################
#build: $(OBJECTS) $(EXECUTABLE:%=objs/%.o) \
#	       $(EXECUTABLE:%=objs/%.out)

all: $(SOURCES) $(EXECUTABLE)
	
#  Build executable files 
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)


#  Build object files 
objs/%.o: DecentralizedParkPilot/%.cpp
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/%.o: Common/Turbine/%.cpp
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/%.o: Common/%.cpp
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/%.o: Common/%.cxx
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

clean:
	@rm -Rf objs/*
	@echo "Deleted all executables, objects and generated files"




