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


/* The class containing DDS event callbacks */
class TurbineStatusListener : public DDSDataReaderListener {
public:
	// ---------------------------------------------------------------------------
	// DDSDataReaderListener interface callbacks
public:
	void on_liveliness_changed(
		DDSDataReader* reader,
		const DDS_LivelinessChangedStatus& status);
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
	long _number_of_turbines;
};