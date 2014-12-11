#pragma once

#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <vector>
#include <ndds/ndds_requestreply_cpp.h>
#include <thread>

#include "RequestMessage.h"
#include "RequestMessageSupport.h"
#include "RequestMessagePlugin.h"

#include "TurbineDataMessage.h"
#include "TurbineDataMessageSupport.h"
#include "TurbineDataMessagePlugin.h"

#include "SetpointMessage.h"
#include "SetpointMessageSupport.h"
#include "SetpointMessagePlugin.h"

#include "TurbineOutlet.h"
#include "CmdArguments.h"

using namespace std;
using namespace connext;

#define GLOBAL_SETPOINT 2000
#define START_ID 1

class CentralizedParkPilot
{
public:
	CentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* setpoint_topic, CmdArguments args);
	
	void calculateNewSetpoints();

private:
	Requester<RequestMessage, TurbineDataMessage> _requester;
	CmdArguments cmdArgs;
	SetpointMessageDataWriter* _setpoint_writer;
	vector<TurbineOutlet*> _turbineOutlets;

	void regAlgorithm(
		uint_fast32_t globalSetpoint,
		LoanedSamples<TurbineDataMessage> &turbines,
		long cycle_time);
};

