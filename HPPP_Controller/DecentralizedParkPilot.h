#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

#include "TurbineMessage.h"
#include "TurbineMessageSupport.h"
#include "TurbineMessagePlugin.h"
#include "MaxProductionReachedMessage.h"
#include "MaxProductionReachedMessagePlugin.h"
#include "MaxProductionReachedMessageSupport.h"
#include "Turbine.h"

using namespace std;

//#define TURBINE_ID 2
#define GLOBAL_SETPOINT 2000

class TurbineStatusListener : public DDSDataReaderListener {
public:
	void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
};

class DecentralizedParkPilot
{
public:
	DecentralizedParkPilot(uint_fast32_t turbineId, DDSDomainParticipant* participant, DDSTopic* cluster_topic, DDSTopic* maxprod_reached_topic);
	~DecentralizedParkPilot();

	void calculateNewSetpoint();

private:
	DDSDataWriter* _writer;
	TurbineStatusListener _listener;
	TurbineMessageDataReader* _reader;
	TurbineMessageDataWriter* _turbine_writer;
	Turbine _turbine;
	uint_fast32_t turbineId;
	chrono::milliseconds _ms_last_write_timestamp;

	MaxProductionReachedMessageDataWriter* _maxProd_reached_writer;

	void productionLevelReached(long localAndMaxDiff);
	void printReceivedTurbineData(TurbineMessageSeq turbines, DDS_SampleInfoSeq turbineInfos);

	uint_fast32_t regAlgorithm(
		uint_fast32_t globalSetpoint,
		TurbineMessageSeq turbines,
		uint_fast32_t maxProd,
		uint_fast32_t currentProd,
		uint_fast32_t setPoint,
		DDS_SampleInfoSeq turbineInfos,
		uint_fast32_t &cacheCount);
};