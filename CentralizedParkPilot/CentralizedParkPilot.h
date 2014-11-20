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

using namespace std;
using namespace connext;

#define GLOBAL_SETPOINT 2000
#define START_ID 1

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
	vector<TurbineOutlet*> _turbineOutlets;

	uint_fast32_t regAlgorithm(
		uint_fast32_t globalSetpoint,
		LoanedSamples<TurbineDataMessage> turbines,
		uint_fast32_t maxProd,
		uint_fast32_t currentProd,
		uint_fast32_t setPoint,
		DDS_SampleInfoSeq turbineInfos,
		uint_fast32_t &cacheCount);
};

