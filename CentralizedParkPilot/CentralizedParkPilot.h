#pragma once

#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <ndds/ndds_requestreply_cpp.h>

#include "RequestMessage.h"
#include "RequestMessageSupport.h"
#include "RequestMessagePlugin.h"

#include "TurbineDataMessage.h"
#include "TurbineDataMessageSupport.h"
#include "TurbineDataMessagePlugin.h"

#include "SetpointMessage.h"
#include "SetpointMessageSupport.h"
#include "SetpointMessagePlugin.h"

using namespace std;
using namespace connext;

class CentralizedParkPilot
{
public:
	CentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* setpoint_topic, uint_fast32_t number_of_turbines);
	~CentralizedParkPilot();
	
	void calculateNewSetpoints();

private:
	Requester<RequestMessage, TurbineDataMessage> _requester;
	uint_fast32_t _number_of_turbines;
	SetpointMessageDataWriter* _setpoint_writer;
};

