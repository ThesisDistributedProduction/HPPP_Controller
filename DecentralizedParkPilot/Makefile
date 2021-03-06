

# The rest of the rules are in the 'Makefile.common'
include ../common.Makefile

ifeq ($(NDDSHOME), )
all:
	@echo "The environment variable 'NDDSHOME' is not set!"
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

.PHONY: all clean buildIDL

CommonLIB = -L./build
IDL_GEN = $(NDDSHOME)/scripts/rtiddsgen2
IDL_FOLDER = ../IDL/

LIBS = -L$(NDDSHOME)/lib/$(ARCH) $(NDDSLIBS) $(CommonLIB) $(MongoLib) $(BOOSTLIBS) $(SYSLIBS)

#INC=-I/usr/informix/incl/c++ /opt/informix/incl/public
INCLUDES=-I../Common \
	-I$(IDL_FOLDER) \
	-I$(NDDSHOME)/include/ \
	-I$(NDDSHOME)/include/ndds

DIRECTORIES = objs

SOURCES = $(wildcard *.cpp)
HEADERS = $(wildcard *.h)

SOURCES_IDL	= $(wildcard $(IDL_FOLDER)*.idl)

SOURCES_IDL_CXX		= $(SOURCES_IDL:%.idl=%.cxx)
SOURCES_IDL_CXX_2 	= $(SOURCES_IDL:%.idl=%Support.cxx)
SOURCES_IDL_CXX_2  += $(SOURCES_IDL:%.idl=%Plugin.cxx)

OBJECTS = $(SOURCES:%=objs/%.o)
OBJECTS += $(SOURCES_IDL_CXX:../%=objs/%.o)
OBJECTS += $(SOURCES_IDL_CXX_2:../%=objs/%.o)

OBJECTS += ../Common/build/common.a


#build: CommonLIB += -lcommon
#build: ./build/libcommon.so buildIDL build/DecentralicedClient
all: buildIDL build/DecentralicedClient

debug: CXX += -DDEBUG -g
debug: CC += -DDEBUG -g
#debug: CommonLIB += -lcommond
#debug: ./build/libcommond.so buildIDL build/DecentralicedClient
debug: buildIDL build/DecentralicedClient

buildIDL: $(SOURCES_IDL) $(SOURCES_IDL_CXX)

build/DecentralicedClient: $(SOURCES) $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBS)

../Common/build/common.a:
		cd ../Common && $(MAKE)

../Common/build/libcommon.so:
		cd ../Common && $(MAKE) build/libcommon.so

../Common/build/libcommond.so:
		cd ../Common && $(MAKE) build/libcommond.so

./build/libcommon.so: ../Common/build/libcommon.so
	@mkdir -p $(@D)
	@cp ../Common/build/libcommon.so ./build/libcommon.so

./build/libcommond.so: ../Common/build/libcommond.so
	@mkdir -p $(@D)
	@cp ../Common/build/libcommond.so ./build/libcommond.so

objs/IDL/%.o: ../IDL/%
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

objs/%.o: % $(HEADERS) 
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<

$(IDL_FOLDER)%.cxx $(IDL_FOLDER)%Support.cxx $(IDL_FOLDER)%Plugin.cxx : $(IDL_FOLDER)%.idl
	@mkdir -p $(@D)
	$(IDL_GEN) -d $(@D)/ -inputIdl $< -language C++

clean:
	@rm -Rf objs
	@rm -Rf build

cleanAll: clean
	cd ../Common && $(MAKE) clean
	@rm -Rf $(IDL_FOLDER)*.cxx
	@rm -Rf $(IDL_FOLDER)*.h
