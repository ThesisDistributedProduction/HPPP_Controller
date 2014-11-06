#include "CentralizedParkPilot.h"

void TurbineListener::on_data_available(DDSDataReader* reader)
{
	TurbineDataMessageSeq turbines;
	DDS_SampleInfoSeq info_seq;
	DDS_ReturnCode_t retcode;

	TurbineDataMessageDataReader* _reader = TurbineDataMessageDataReader::narrow(reader);
	if (_reader == NULL) {
		printf("DataReader narrow error\n");
		throw runtime_error("Unable to narrow data reader into TurbineDataReader");
	}

	retcode = _reader->take(
		turbines,
		info_seq, 
		DDS_LENGTH_UNLIMITED,
		DDS_ANY_SAMPLE_STATE, 
		DDS_ANY_VIEW_STATE, 
		DDS_ANY_INSTANCE_STATE);

	if (retcode == DDS_RETCODE_NO_DATA) {
		return;
	}
	else if (retcode != DDS_RETCODE_OK) {
		printf("take error %d\n", retcode);
		return;
	}

	for (int i = 0; i < turbines.length(); ++i) {
		if (info_seq[i].valid_data) {
			TurbineDataMessageTypeSupport::print_data(&turbines[i]);
		}
	}

	retcode = _reader->return_loan(turbines, info_seq);
	if (retcode != DDS_RETCODE_OK) {
		printf("return loan error %d\n", retcode);
	}
}


CentralizedParkPilot::CentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* request_topic, DDSTopic* reply_topic)
{
	DDSPublisher* publisher = participant->create_publisher(
		DDS_PUBLISHER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (publisher == NULL) {
		printf("create_publisher error\n");
		throw runtime_error("Unable to create DataPublisher");
	}

	DDSDataWriter* _writer = publisher->create_datawriter(
		request_topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (_writer == NULL) {
		printf("create_datawriter error\n");
		throw runtime_error("Unable to create writer");
	}

	_request_writer = RequestMessageDataWriter::narrow(_writer);
	if (_request_writer == NULL) {
		printf("DataWriter narrow error\n");
		throw runtime_error("Unable to create turbine_writer");
	}


	DDSSubscriber *subscriber = participant->create_subscriber(
		DDS_SUBSCRIBER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (subscriber == NULL) {
		printf("create_subscriber error\n");
		throw runtime_error("Unable to create subscriber");
	}

	DDSDataReader* untypedReader = subscriber->create_datareader(
		reply_topic,
		DDS_DATAREADER_QOS_DEFAULT,
		&_listener,
		DDS_STATUS_MASK_ALL);			//(DDS_DATA_AVAILABLE_STATUS)
	if (untypedReader == NULL) {
		printf("create_datareader error\n");
		throw runtime_error("Unable to create DataReader");
	}
}

CentralizedParkPilot::~CentralizedParkPilot()
{
}

void CentralizedParkPilot::calculateNewSetpoints()
{
	int sample_count = 0;
	DDS_Duration_t receive_period = { 0, 150000000 }; //150 ms
	DDS_Duration_t sleep_time = { 0, 10000000 }; //10 ms
	DDS_ReturnCode_t retcode;
	chrono::milliseconds ms_last_write_timestamp = chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now().time_since_epoch());

	RequestMessage* instance = RequestMessageTypeSupport::create_data();
	/*instance->msSinceLastWrite = _turbine->getTurbineId();
	instance_handle = _turbine_data_writer->register_instance(*instance);*/

	//instance->cacheCount = cacheCount;


	for (int count = 0; (sample_count == 0) || (count < sample_count); ++count) {

		instance->msSinceLastWrite = (chrono::duration_cast< chrono::milliseconds >(
			chrono::high_resolution_clock::now().time_since_epoch()) - ms_last_write_timestamp).count();

		retcode = _request_writer->write(*instance, DDS_HANDLE_NIL);

		//update timestamp
		ms_last_write_timestamp = chrono::duration_cast<chrono::milliseconds>(
			chrono::high_resolution_clock::now().time_since_epoch()
			);

		
		while (!_allDataReceived)
		{
			NDDSUtility::sleep(sleep_time);
		}

		if (retcode != DDS_RETCODE_OK) {
			 cerr << "Write failed: " << retcode << endl;
			 return;
		}

		printf("Centralized park pilot subscriber sleeping for %d ms...\n",
			(receive_period.nanosec / 1000000) );

		NDDSUtility::sleep(receive_period);
	}
}
