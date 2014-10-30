#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "Turbine.h"
#include "TurbineSupport.h"
#include "TurbinePlugin.h"
#include "MaxProductionReachedMessage.h"
#include "MaxProductionReachedMessagePlugin.h"
#include "MaxProductionReachedMessageSupport.h"

using namespace std;

#define TURBINE_ID 2
#define GLOBAL_SETPOINT 2000
#define MAX_PRODUCTION 500
#define CURRENT_PRODUCTION 200

class TurbineStatusListener : public DDSDataReaderListener {
public:
	void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
};

class DecentralizedParkPilot
{
public:
	DecentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* cluster_topic, DDSTopic* maxprod_reached_topic);
	~DecentralizedParkPilot();

	void calculateNewSetpoint();

private:
	DDSDataWriter* _writer;
	TurbineStatusListener _listener;
	TurbineDataReader* _reader;
	TurbineDataWriter* _turbine_writer;

	MaxProductionReachedMessageDataWriter* _maxProd_reached_writer;
	long regAlgorithm(long globalSetpoint, TurbineSeq turbines, long maxProd, long currentProd, DDS_SampleInfoSeq turbineInfos);
	void productionLevelReached(long localAndMaxDiff);
	void printReceivedTurbineData(TurbineSeq turbines, DDS_SampleInfoSeq turbineInfos);
};