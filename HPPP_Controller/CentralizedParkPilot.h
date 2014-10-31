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
	DDSDataWriter* _writer;
	DDSStringDataWriter* _turbine_writer;
	bool _allDataReceived;
};

