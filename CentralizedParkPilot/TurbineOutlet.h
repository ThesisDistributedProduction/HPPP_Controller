#pragma once

#include <string>
#include <iostream>

#include "SetpointMessage.h"
#include "SetpointMessagePlugin.h"
#include "SetpointMessageSupport.h"

using namespace std;

class TurbineOutlet
{
public:
	TurbineOutlet(long turbineId, SetpointMessageDataWriter* theWriter)
		: _writer(theWriter),
		_handle(DDS_HANDLE_NIL) 
	{ 
		_instance = SetpointMessageTypeSupport::create_data();
		_instance->turbineId = turbineId;
	}

	~TurbineOutlet();

	void publishData()
	{
		_instance->setPoint = _setPoint;

		DDS_ReturnCode_t retcode = _writer->write(*_instance, _handle);

		if (retcode != DDS_RETCODE_OK) {
			printf("write error %d\n", retcode);
			throw runtime_error("write error " + retcode);
		}
	}

	void setCurProd(long curProd) { _curProd = curProd; }
	void setMaxProd(long maxProd) { _maxProd = maxProd; }
	void setSetpoint(long setPoint) { _setPoint = setPoint; }

	long getCurProd() { return _curProd; }
	long getMaxProd() { return _maxProd; }
	long getSetpoint() { return _setPoint; }

	void registerTurbine()
	{
		_handle = _writer->register_instance(*_instance);
	}

private:
	long _curProd;
	long _maxProd;
	long _setPoint;
	SetpointMessage* _instance;
	SetpointMessageDataWriter* _writer;
	DDS_InstanceHandle_t _handle;
};

