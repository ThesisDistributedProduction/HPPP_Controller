#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>
#include <chrono>
#include <sstream>

#include "RequestMessage.h"
#include "RequestMessageSupport.h"
#include "RequestMessagePlugin.h"

#include "TurbineDataMessage.h"
#include "TurbineDataMessageSupport.h"
#include "TurbineDataMessagePlugin.h"

#include "SetpointMessage.h"
#include "SetpointMessageSupport.h"
#include "SetpointMessagePlugin.h"

#include "Turbine.h"

using namespace std;

class RequestListener : public DDSDataReaderListener {
public:
	//void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
	RequestListener(Turbine& turbine, DDSDomainParticipant* participant, DDSTopic* reply_topic);
	~RequestListener();

	virtual void on_data_available(DDSDataReader* reader);
private:
	Turbine* _turbine;
	TurbineDataMessageDataWriter* _turbine_data_writer;
	TurbineDataMessage* instance;
	DDS_InstanceHandle_t instance_handle;
};

class SetpointListener : public DDSDataReaderListener {
public:
	//void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
	SetpointListener(Turbine& turbine);
	~SetpointListener();

	virtual void on_data_available(DDSDataReader* reader);
private:
	Turbine* _turbine;
};



class TurbineCentralized
{
public:
	TurbineCentralized(Turbine& turbine, DDSDomainParticipant* participant, DDSTopic* request_topic, DDSTopic* reply_topic, DDSTopic* setpoint_topic);
	~TurbineCentralized();
private:
	RequestListener _request_listener;
	SetpointListener _setpoint_listener;
};

