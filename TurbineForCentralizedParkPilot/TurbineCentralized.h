#pragma once

#include <ndds/ndds_cpp.h>
#include <ndds/ndds_requestreply_cpp.h>
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
using namespace connext;

class SetpointListener : public DDSDataReaderListener {
public:
	//void on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status);
	SetpointListener(Turbine& turbine);
	~SetpointListener() { }

	virtual void on_data_available(DDSDataReader* reader);
private:
	Turbine* _turbine;
};


class TurbineDataRequestListener : public SimpleReplierListener < RequestMessage, TurbineDataMessage > {
public:
	TurbineDataRequestListener(Turbine& turbine)
	{
		cout << "Turbine " << turbine.getTurbineId() << " ONLINE" << endl;
		this->_turbine = &turbine;
		this->_turbine->sendSetpoint(0);
	}

	~TurbineDataRequestListener() { }

	TurbineDataMessage* on_request_available(SampleRef<RequestMessage> request)
	{
		cout << "on_request_available" << endl;
		uint_fast32_t curProd = 0;
		uint_fast32_t maxProd = 0;

		if (!request.info().valid_data) {
			return NULL;
		}
		cout << "Cycle time(ms): " << request.data().msSinceLastWrite;

		_turbine->readTurbineData(maxProd, curProd);

		_reply.data().turbineId = _turbine->getTurbineId();
		_reply.data().currentProduction = curProd;
		_reply.data().maxProduction = maxProd;

		cout << " Id: " << _reply.data().turbineId << " CurProd: " << _reply.data().currentProduction << " MaxProd: " << _reply.data().maxProduction << endl;

		return &_reply.data();
	}

	void return_loan(TurbineDataMessage* reply) 
	{ 
		cout << "return_loan" << endl;
	}
private:
	Turbine* _turbine;
	WriteSample<TurbineDataMessage> _reply;
};


class TurbineCentralized
{
public:
	TurbineCentralized(Turbine& turbine, DDSDomainParticipant* participant, DDSTopicDescription* cft_setpoint_topic);
	~TurbineCentralized() { }

	void waitForRequests()
	{
		DDS_Duration_t MAX_WAIT = { 0, 10000000 }; //10 ms
		uint_fast32_t curProd = 0;
		uint_fast32_t maxProd = 0;
		while (true) {
			Sample<RequestMessage> request;
			// Receive one request
			bool received = _replier.receive_request(request, MAX_WAIT);
			if (!received) {
				continue;
			}

			WriteSample<TurbineDataMessage> _reply;
			if (request.info().valid_data) {

				_turbine->readTurbineData(maxProd, curProd);

				_reply.data().turbineId = _turbine->getTurbineId();
				_reply.data().currentProduction = curProd;
				_reply.data().maxProduction = maxProd;

				time_t src_time = (time_t)request.info().source_timestamp.sec;
				tm* local_src_time = localtime(&src_time);

				cout << "\r";
				cout << " [" << std::setw(2) << std::setfill('0') << local_src_time->tm_hour
					<< ":" << std::setw(2) << std::setfill('0')
					<< local_src_time->tm_min
					<< ":" << std::setw(2) << std::setfill('0')
					<< local_src_time->tm_sec << "] ";
				cout << setfill(' ') << setw(3) << _reply.data().turbineId;
				cout << setfill(' ') << setw(6) << _reply.data().currentProduction;
				cout << setfill(' ') << setw(6) << _reply.data().maxProduction;
				cout << setfill(' ') << setw(8) << request.data().msSinceLastWrite;

				std::cout.flush();

				_replier.send_reply(_reply, request.identity());
			}
		}
	}
private:
	//TurbineDataRequestListener _request_listener;
	SetpointListener _setpoint_listener;
	Replier<RequestMessage, TurbineDataMessage> _replier;
	Turbine* _turbine;
};

