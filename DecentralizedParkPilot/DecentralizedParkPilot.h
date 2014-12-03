#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "TurbineMessage.h"
#include "TurbineMessageSupport.h"
#include "TurbineMessagePlugin.h"
#include "MaxProductionReachedMessage.h"
#include "MaxProductionReachedMessagePlugin.h"
#include "MaxProductionReachedMessageSupport.h"
#include "iTurbine.h"
#include "CmdArguments.h"

using namespace std;
using namespace boost::posix_time;

class DecentralizedParkPilot
{
public:
	DecentralizedParkPilot(CmdArguments args, DDSDomainParticipant* participant, DDSTopic* cluster_topic, DDSTopic* maxprod_reached_topic);

	void calculateNewSetpoint();

private:
	DDSDataWriter* _writer;
	//TurbineStatusListener _listener;
	TurbineMessageDataReader* _reader;
	TurbineMessageDataWriter* _turbine_writer;
	std::shared_ptr<iTurbine> _turbine;
	CmdArguments cmdArgs;
	chrono::nanoseconds _ms_last_write_timestamp;
	unsigned short fractionWidth = time_duration::num_fractional_digits();

	static const int CYCLE_AVG_BUFFER_SIZE = 200;
	uint_fast32_t cycleAvgBuffer[CYCLE_AVG_BUFFER_SIZE];
	uint_fast32_t cycleAvgBufferIndex = 0;

	MaxProductionReachedMessageDataWriter* _maxProd_reached_writer;

	void productionLevelReached(long localAndMaxDiff);
	void printReceivedTurbineData(TurbineMessageSeq turbines, DDS_SampleInfoSeq turbineInfos);
	uint_fast32_t calculateCycleTime(DDS_SampleInfoSeq turbineInfos);

	uint_fast32_t regAlgorithm(
		uint_fast32_t globalSetpoint,
		TurbineMessageSeq turbines,
		uint_fast32_t maxProd,
		uint_fast32_t currentProd,
		uint_fast32_t setPoint,
		DDS_SampleInfoSeq turbineInfos,
		uint_fast32_t &cacheCount);
};
