#include "CmdArguments.h"

CmdArguments parseCmdLineArgs(int argc, char *argv[]) {
	const char ID[] = "-id";
	const char MSLEEP[] = "-msleep";
	const char SETPOINT[] = "-sp";
	const char VERBOSE[] = "-s";
	const char NUMBER_OF_TURBINES[] = "-n";
	CmdArguments args;

	uint32_t i = 0;
	while( argc > i ) {
		char *argument = argv[i];
		if( argument[0] != '-') {
			i++;
			continue;
		}

		if( strcmp(argument, ID) == 0 && argc > i+1) {
			args.id = atoi(argv[i + 1]);
			i++;

		} else if( strcmp(argument, MSLEEP) == 0 && argc > i + 1 ) {
			args.msleep = atoi(argv[i + 1]);
			i++;

		} else if( strcmp(argument, SETPOINT) == 0 && argc > i + 1 ) {
			args.setpoint = atoi(argv[i + 1]);
			i++;

		} else if( strcmp(argument, NUMBER_OF_TURBINES) == 0 && argc > i + 1 ) {
			args.numberOfTurbines = atoi(argv[i + 1]);
			i++;

		} else if( strcmp(argument, VERBOSE) == 0 && argc ) {
			args.silent = true;

		}

		i++;
	}


	return args;
}