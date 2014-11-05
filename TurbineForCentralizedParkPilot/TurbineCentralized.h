#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "TurbineMessage.h"
#include "TurbineMessageSupport.h"
#include "TurbineMessagePlugin.h"

using namespace std;

class RequestListener : public DDSDataReaderListener {
public:
	//void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);

	virtual void on_data_available(DDSDataReader* reader);
};

class TurbineCentralized
{
public:
	TurbineCentralized(DDSDomainParticipant* participant, DDSTopic* request_topic, DDSTopic* reply_topic);
	~TurbineCentralized();
private:
	RequestListener _listener;
	TurbineMessageDataWriter* _turbine_data_writer;
};

