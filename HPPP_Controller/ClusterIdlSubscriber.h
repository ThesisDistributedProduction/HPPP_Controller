#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "Turbine.h"
#include "TurbineSupport.h"
#include "TurbinePlugin.h"

using namespace std;

class TurbineStatusListener : public DDSDataReaderListener {
public:
	void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
};

class ClusterIdlSubscriber
{
public:
	ClusterIdlSubscriber(DDSDomainParticipant* participant, DDSTopic* topic);
	~ClusterIdlSubscriber();

	void calculateNewSetpoint();

private:
	TurbineStatusListener _listener;
	TurbineDataReader* _reader;
	DDSDataWriter* _writer;
	TurbineDataWriter* _turbine_writer;
};