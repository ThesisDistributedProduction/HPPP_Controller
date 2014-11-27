#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>

#include "TurbineMessage.h"
#include "TurbineMessageSupport.h"
#include "TurbineMessagePlugin.h"
#include "MaxProductionReachedMessage.h"
#include "MaxProductionReachedMessagePlugin.h"
#include "MaxProductionReachedMessageSupport.h"
#include "iTurbine.h"
#include "CmdArguments.h"

using namespace std;

//class TurbineStatusListener : public DDSDataReaderListener {
//public:
//	void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
//};

class DecentralizedParkPilot
{
public:
	DecentralizedParkPilot(CmdArguments args, DDSDomainParticipant* participant, DDSTopic* cluster_topic, DDSTopic* maxprod_reached_topic);
	~DecentralizedParkPilot();

	void calculateNewSetpoint();

private:
	DDSDataWriter* _writer;
	//TurbineStatusListener _listener;
	TurbineMessageDataReader* _reader;
	TurbineMessageDataWriter* _turbine_writer;
	std::shared_ptr<iTurbine> _turbine;
	CmdArguments cmdArgs;
	chrono::nanoseconds _ms_last_write_timestamp;

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