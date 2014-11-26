

# The rest of the rules are in the 'Makefile.common'
include ../common.Makefile

.PHONY: clean build debug

# PIC = position independent code, used for libaries
CFLAGS += -fPIC
LDFLAGS += -shared

MongoClentInclude = -I../MongoClientLib/include

LIBS = $(SYSLIBS) $(BOOSTLIBS) $(MongoLib)

INCLUDES= $(MongoClentInclude) \
	-I./Common

DIRECTORIES = objs

SOURCES	= $(wildcard *.cpp) \
		  $(wildcard Turbine/*.cpp)

OBJECTS = $(SOURCES:%=objs/%.o)

buld: build/common.a

debug: CXX += -DDEBUG -g
debug: CC += -DDEBUG -g
debug: build/commond.a

build/common.a: $(SOURCES) $(OBJECTS)
	@mkdir -p $(@D)
	ar -cvq $@ $(OBJECTS)

build/commond.a: CXX += -DDEBUG -g
build/commond.a: CC += -DDEBUG -g
build/commond.a: $(SOURCES) $(OBJECTS)
	@mkdir -p $(@D)
	ar -cvq $@ $(OBJECTS)

build/libcommon.so: $(SOURCES) $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@ -Wl,-soname,$@

build/libcommond.so: CXX += -DDEBUG -g
build/libcommond.so: CC += -DDEBUG -g
build/libcommond.so: $(SOURCES) $(OBJECTS)
	@mkdir -p $(@D)
	$(CC) $(LDFLAGS) $(OBJECTS) $(LIBS) -o $@ -Wl,-soname,$@

objs/%.o: %
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ $(DEFINES) $(INCLUDES) -c $<


clean:
	@rm -Rf objs
	@rm -Rf build
