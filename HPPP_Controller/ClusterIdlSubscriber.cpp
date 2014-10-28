#include "ClusterIdlSubscriber.h"


void TurbineStatusListener::on_liveliness_changed(
	DDSDataReader* reader,
	const DDS_LivelinessChangedStatus& status) {

	Turbine turbine;
	TurbineDataReader* typedReader =
		TurbineDataReader::narrow(reader);


	DDS_ReturnCode_t retcode = typedReader->get_key_value(turbine, status.last_publication_handle);

	//DDS_RETCODE_BAD_PARAMETER

	if (status.alive_count_change > 0)
	{
		std::cout << "\nTurbine went ONLINE."
			<< " recode: " << retcode
			<< " keyHash.value: " << status.last_publication_handle.keyHash.value
			/*<< " Id: " << turbine.turbineId
			<< " Prod: " << turbine.currentProduction*/
			<< std::endl;
	}
	else if (status.alive_count_change < 0)
	{
		std::cout << "\nTurbine went OFFLINE."
			<< " recode: " << retcode
			<< " keyHash.value: " << status.last_publication_handle.keyHash.value
			<< std::endl;
	}
	else 
		std::cout << "\nNo change"
		/*<< turbine.turbineId*/
		<< std::endl;

	
	if (!status.last_publication_handle.isValid) {
		std::cout << "not valid";
	}
	/*std::cout << "->Callback: Turbine went offline."
		<< turbine.turbineId
		<< std::endl;

	TurbineSeq turbines;
	DDS_SampleInfoSeq turbineInfos;
	typedReader->take_instance_w_condition(turbines, turbineInfos, DDS_LENGTH_UNLIMITED,ddshandle,);


	DDS_LENGTH_UNLIMITED,
		DDS_ANY_SAMPLE_STATE,
		DDS_ANY_VIEW_STATE,
		DDS_ANY_INSTANCE_STATE);*/

}

ClusterIdlSubscriber::ClusterIdlSubscriber(DDSDomainParticipant* participant, DDSTopic* topic)
{
	/* To customize the data reader QoS, use
	the configuration file USER_QOS_PROFILES.xml */
	_number_of_turbines = 0;

	DDSDataReader* untypedReader = participant->create_datareader(
		topic, 
		DDS_DATAREADER_QOS_DEFAULT, 
		&_listener,							 
		DDS_STATUS_MASK_ALL);			//(DDS_DATA_AVAILABLE_STATUS)
	if (untypedReader == NULL) {
		printf("create_datareader error\n");
		throw std::runtime_error("Unable to create DataReader");
	}

	_reader = TurbineDataReader::narrow(untypedReader);

	/*DDS_ReturnCode_t retcode;

	DDS_DataReaderQos BLA;

	retcode = _reader->get_qos(BLA);
	if (retcode != DDS_RETCODE_OK) {
		std::cerr << "! Unable to get participant factory QoS: "
			<< retcode << std::endl;
		return;
	}

	cout << "QOS: Depth: " << BLA.history.depth << endl;

	 BLA.history.depth = 10;

	 retcode = _reader->set_qos(BLA);
	if (retcode != DDS_RETCODE_OK) {
		std::cerr << "! Unable to set participant factory QoS: "
			<< retcode << std::endl;
		return;
	}
*/

	if (_reader == NULL) {
		throw std::runtime_error(
			"Unable to narrow data reader into TurbineDataReader");
	}
}


ClusterIdlSubscriber::~ClusterIdlSubscriber() { }

void ClusterIdlSubscriber::calculateNewSetpoint()
{
	TurbineSeq turbines;
	DDS_SampleInfoSeq turbineInfos;
	DDS_ReturnCode_t retcode;
	int i;

	if (_reader == NULL) {
		printf("DataReader narrow error\n");
		return;
	}

	int sample_count = 0; /* infinite loop */
	int count = 0;

	for (count = 0; (sample_count == 0) || (count < sample_count); ++count) {

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
			throw std::runtime_error("A read error occurred: " + result);
		}
		
		for (i = 0; i < turbines.length(); ++i) {
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
			std::cout
				<< "[" << local_src_time->tm_hour
				<< ":" << std::setw(2) << std::setfill('0')
				<< local_src_time->tm_min
				<< ":" << std::setw(2) << std::setfill('0')
				<< local_src_time->tm_sec << "] ";
			cout << "Id: " << turbineData.turbineId;
			cout << ", Curr. prod.: " << turbineData.currentProduction;


			if (turbineInfo.sample_state == DDS_READ_SAMPLE_STATE) {
				std::cout << " (cached)";
			}

		}

		/* For the sake of efficiency, we're using object pools
		* maintained by the middleware. Return the objects to the
		* pool so that the middleware can recycle them.
		*/
		result = _reader->return_loan(turbines, turbineInfos);
		if (result != DDS_RETCODE_OK) {
			// an error occurred: stop reading
			throw std::runtime_error(
				"A loan return error occurred: " + result);
		}

	sleep:
		Sleep(150);
	}
}
