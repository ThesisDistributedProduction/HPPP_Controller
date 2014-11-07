#include "TurbineCentralized.h"

RequestListener::RequestListener(Turbine& turbine, DDSDomainParticipant* participant, DDSTopic* reply_topic)
{
	this->_turbine = &turbine;
	this->_turbine->sendSetpoint(0);

	DDSPublisher* publisher = participant->create_publisher(
		DDS_PUBLISHER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (publisher == NULL) {
		printf("create_publisher error\n");
		throw runtime_error("Unable to create DataPublisher");
	}

	DDSDataWriter* _writer = publisher->create_datawriter(
		reply_topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (_writer == NULL) {
		printf("create_datawriter error\n");
		throw runtime_error("Unable to create writer");
	}

	_turbine_data_writer = TurbineDataMessageDataWriter::narrow(_writer);
	if (_turbine_data_writer == NULL) {
		printf("_turbine_data_writer narrow error\n");
		throw runtime_error("Unable to create _turbine_data_writer");
	}

	instance = TurbineDataMessageTypeSupport::create_data();
	instance->turbineId = _turbine->getTurbineId();
	instance_handle = _turbine_data_writer->register_instance(*instance);
}

RequestListener::~RequestListener()
{
}

void RequestListener::on_data_available(DDSDataReader* reader)
{
	DDS_ReturnCode_t retcode;
	DDS_SampleInfo info;
	uint_fast32_t curProd = 0;
	uint_fast32_t maxProd = 0;
	RequestMessage req;

	RequestMessageDataReader* _reader = RequestMessageDataReader::narrow(reader);
	if (_reader == NULL) {
		printf("DataReader narrow error\n");
		throw runtime_error("Unable to narrow data reader into RequestMessageDataReader");
	}

	for (;;) {
		retcode = _reader->take_next_sample(req, info);

		if (retcode == DDS_RETCODE_NO_DATA) {
			break;
		}
		else if (retcode != DDS_RETCODE_OK) {
			printf("take error %d\n", retcode);
			return;
		}
		if (info.valid_data) {
			cout << "Cycle time(ms): " << req.msSinceLastWrite;

			_turbine->readTurbineData(maxProd, curProd);

			instance->currentProduction = curProd;
			instance->maxProduction = maxProd;

			cout << " Id: " << instance->turbineId << " CurProd: " << instance->currentProduction << " MaxProd: " << instance->maxProduction << endl;

			retcode = _turbine_data_writer->write(*instance, instance_handle);

			if (retcode != DDS_RETCODE_OK) {
				printf("write error %d\n", retcode);
				throw runtime_error("write error " + retcode);
			}
		}
	}
}


SetpointListener::SetpointListener(Turbine& turbine)
{
	this->_turbine = &turbine;
}

SetpointListener::~SetpointListener()
{}

void SetpointListener::on_data_available(DDSDataReader* reader)
{
	DDS_ReturnCode_t retcode;
	DDS_SampleInfo info;
	SetpointMessage setPointMsg;

	SetpointMessageDataReader* _reader = SetpointMessageDataReader::narrow(reader);
	if (_reader == NULL) {
		printf("DataReader narrow error\n");
		throw runtime_error("Unable to narrow data reader into SetpointMessageDataReader");
	}

	for (;;) {
		retcode = _reader->take_next_sample(setPointMsg, info);

		if (retcode == DDS_RETCODE_NO_DATA) {
			break;
		}
		else if (retcode != DDS_RETCODE_OK) {
			printf("take error %d\n", retcode);
			return;
		}
		if (info.valid_data) {

			cout << "Setpoint: " << setPointMsg.setPoint << endl;

			_turbine->sendSetpoint(setPointMsg.setPoint);
		}
	}
}


TurbineCentralized::TurbineCentralized(Turbine& turbine, DDSDomainParticipant* participant, DDSTopic* request_topic, DDSTopic* reply_topic, DDSTopic* setpoint_topic)
	: _request_listener(turbine, participant, reply_topic), _setpoint_listener(turbine)
{
	DDSSubscriber *subscriber = participant->create_subscriber(
		DDS_SUBSCRIBER_QOS_DEFAULT,
		NULL,
		DDS_DATA_AVAILABLE_STATUS);
	if (subscriber == NULL) {
		printf("create_subscriber error\n");
		throw runtime_error("Unable to create subscriber");
	}

	DDSDataReader* untypedRequestReader = subscriber->create_datareader(
		request_topic,
		DDS_DATAREADER_QOS_DEFAULT,
		&_request_listener,
		DDS_DATA_AVAILABLE_STATUS);			
	if (untypedRequestReader == NULL) {
		printf("create_datareader error\n");
		throw runtime_error("Unable to create untypedRequestReader");
	}

	DDSDataReader* untypedSetpointReader = subscriber->create_datareader(
		setpoint_topic,
		DDS_DATAREADER_QOS_DEFAULT,
		&_setpoint_listener,
		DDS_DATA_AVAILABLE_STATUS);
	if (untypedSetpointReader == NULL) {
		printf("create_datareader error\n");
		throw runtime_error("Unable to create untypedSetpointReader");
	}
}

TurbineCentralized::~TurbineCentralized()
{
}
