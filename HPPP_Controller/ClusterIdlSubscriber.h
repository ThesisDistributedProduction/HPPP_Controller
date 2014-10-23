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

class ClusterIdlSubscriber
{
public:
	ClusterIdlSubscriber(DDSDomainParticipant* participant, DDSTopic* topic);
	~ClusterIdlSubscriber();

	void calculateNewSetpoint();

private:
	//ArticleDeliveryStatusListener _listener;
	TurbineDataReader* _reader;
};