#pragma once

#include <ndds/ndds_cpp.h>
#include <time.h>
#include <string>
#include <iostream>
#include <iomanip>

#include "TurbineMessage.h"

using namespace std;

#define STATUS_PERIOD_MILLIS    (2 * 1000)

class ClusterSubscriber
{
public:
	ClusterSubscriber(
		DDSDomainParticipant* participant,
		DDSTopic* topic);

	~ClusterSubscriber();

	void calculateNewSetpoint();

private:
	//ArticleDeliveryStatusListener _listener;
	DDS_Long _verbosity;
	DDS_Long _runSeconds;
	DDSKeyedOctetsDataReader* _reader;
};

