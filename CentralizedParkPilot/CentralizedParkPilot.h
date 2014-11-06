#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>

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

class TurbineListener : public DDSDataReaderListener {
public:
	//void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);

	virtual void on_data_available(DDSDataReader* reader);
};


class CentralizedParkPilot
{
public:
	CentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* request_topic, DDSTopic* reply_topic);
	~CentralizedParkPilot();
	
	void calculateNewSetpoints();

private:
	TurbineListener _listener;
	RequestMessageDataWriter* _request_writer;
	bool _allDataReceived;
};

