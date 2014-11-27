#pragma once

#include <cstring>
#include <cstdint>
#include <cstdlib>

struct CmdArguments {
	int id = 0;									// -id
	int msleep = 20;						// -msleep
	int setpoint = 2000;				// -sp
	bool silent = false;				// -s (silent)
	int numberOfTurbines = -1;	// -n
};


CmdArguments parseCmdLineArgs(int argc, char *argv[]);