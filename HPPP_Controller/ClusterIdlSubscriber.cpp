#include "ClusterIdlSubscriber.h"


void TurbineStatusListener::on_liveliness_changed(DDSDataReader* reader, const DDS_LivelinessChangedStatus& status) 
{
	if (status.alive_count_change > 0)
		cout << "\nTurbine went ONLINE." << std::endl;
	else if (status.alive_count_change < 0)
		cout << "\nTurbine went OFFLINE." << std::endl;
	else 
		cout << "\nNo change" << std::endl;

	if (!status.last_publication_handle.isValid) {
		cout << "\nTurbine not valid.";
	}
}

ClusterIdlSubscriber::ClusterIdlSubscriber(DDSDomainParticipant* participant, DDSTopic* topic)
{
	DDSDataReader* untypedReader = participant->create_datareader(
		topic, 
		DDS_DATAREADER_QOS_DEFAULT, 
		&_listener,							 
		DDS_STATUS_MASK_ALL);			//(DDS_DATA_AVAILABLE_STATUS)
	if (untypedReader == NULL) {
		printf("create_datareader error\n");
		throw runtime_error("Unable to create DataReader");
	}

	_reader = TurbineDataReader::narrow(untypedReader);
	if (_reader == NULL) {
		throw runtime_error("Unable to narrow data reader into TurbineDataReader");
	}


	DDSPublisher* publisher = participant->create_publisher(
		DDS_PUBLISHER_QOS_DEFAULT, 
		NULL /* listener */, 
		DDS_STATUS_MASK_NONE);
	if (publisher == NULL) {
		printf("create_publisher error\n");
		throw runtime_error("Unable to create DataPublisher");
	}

	_writer = publisher->create_datawriter(
		topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL /* listener */,
		DDS_STATUS_MASK_NONE);
	if (_writer == NULL) {
		printf("create_datawriter error\n");
		throw runtime_error("Unable to create writer");
	}

	_turbine_writer = TurbineDataWriter::narrow(_writer);
	if (_turbine_writer == NULL) {
		printf("DataWriter narrow error\n");
		throw runtime_error("Unable to create turbine_writer");
	}
}


ClusterIdlSubscriber::~ClusterIdlSubscriber() { }

void ClusterIdlSubscriber::calculateNewSetpoint()
{
	TurbineSeq turbines;
	DDS_SampleInfoSeq turbineInfos;
	DDS_ReturnCode_t retcode;
	int sample_count = 0; /* infinite loop */

	if (_reader == NULL) {
		printf("DataReader narrow error\n");
		return;
	}

	Turbine *instance = TurbineTypeSupport::create_data();
	instance->turbineId = 2;
	DDS_InstanceHandle_t instance_handle = _turbine_writer->register_instance(*instance);

	for (int count = 0; (sample_count == 0) || (count < sample_count); ++count) {
		
		DDS_ReturnCode_t result = _reader->read(
			turbines,             
			turbineInfos,
			DDS_LENGTH_UNLIMITED,
			DDS_ANY_SAMPLE_STATE,
			DDS_ANY_VIEW_STATE,
			DDS_ANY_INSTANCE_STATE);

		if (result == DDS_RETCODE_NO_DATA) {
			goto sleep;
		}
		if (result != DDS_RETCODE_OK) {
			throw runtime_error("A read error occurred: " + result);
		}
		
		for (int i = 0; i < turbines.length(); ++i) {
			cout << "\n";
			cout << turbines.length();
			
			DDS_SampleInfo& turbineInfo = turbineInfos[i];

			if (!turbineInfo.valid_data) {
				cout << " Id: " << turbines[i].turbineId;
				cout << ", Curr. prod.: " << turbines[i].currentProduction << endl;;
				cout << " instance_state: " << turbineInfo.instance_state << endl;
				cout << " instance_handle: " << turbineInfo.instance_handle.isValid << endl;
				cout << " view_state: " << turbineInfo.view_state << endl;
				cout << " sample_state: " << turbineInfo.sample_state << endl;
				cout << " timestamp: " << turbineInfo.source_timestamp.from_seconds << endl;
				continue;
			}

			Turbine& turbineData = turbines[i];

			time_t src_time = (time_t)turbineInfo.source_timestamp.sec;
			tm* local_src_time = localtime(&src_time);
			cout << "[" << local_src_time->tm_hour
				 << ":" << std::setw(2) << std::setfill('0')
				 << local_src_time->tm_min
				 << ":" << std::setw(2) << std::setfill('0')
				 << local_src_time->tm_sec << "] ";
			cout << "Id: " << turbineData.turbineId;
			cout << ", Curr. prod.: " << turbineData.currentProduction;


			if (turbineInfo.sample_state == DDS_READ_SAMPLE_STATE) {
				cout << " (cached)";
			}

			//regulering

		}

		result = _reader->return_loan(turbines, turbineInfos);
		if (result != DDS_RETCODE_OK) {
			throw runtime_error("A loan return error occurred: " + result);
		}

		instance->currentProduction = 80;
		instance->maxProduction = 80;
		instance->setPoint = 10;

		retcode = _turbine_writer->write(*instance, instance_handle);

		if (retcode != DDS_RETCODE_OK) {
			printf("write error %d\n", retcode);
			throw runtime_error("write error " + retcode);
		}
	sleep:
		Sleep(50);
	}
}
