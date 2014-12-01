#include "DecentralizedParkPilot.h"

DecentralizedParkPilot::DecentralizedParkPilot(CmdArguments args, DDSDomainParticipant* participant, DDSTopic* cluster_topic, DDSTopic* maxprod_reached_topic)
{
	this->cmdArgs = args;
	_turbine = createTurbineInstance(cmdArgs.id);
	this->_ms_last_write_timestamp = chrono::duration_cast< chrono::nanoseconds >(
		chrono::high_resolution_clock::now().time_since_epoch()
		);

	DDSDataReader* untypedReader = participant->create_datareader(
		cluster_topic,
		DDS_DATAREADER_QOS_DEFAULT, 
		NULL,							 
		DDS_STATUS_MASK_ALL);			//(DDS_DATA_AVAILABLE_STATUS)
	if (untypedReader == NULL) {
		printf("create_datareader error\n");
		throw runtime_error("Unable to create DataReader");
	}

	_reader = TurbineMessageDataReader::narrow(untypedReader);
	if (_reader == NULL) {
		throw runtime_error("Unable to narrow data reader into TurbineDataReader");
	}


	DDSPublisher* publisher = participant->create_publisher(
		DDS_PUBLISHER_QOS_DEFAULT, 
		NULL, 
		DDS_STATUS_MASK_NONE);
	if (publisher == NULL) {
		printf("create_publisher error\n");
		throw runtime_error("Unable to create DataPublisher");
	}

	_writer = publisher->create_datawriter(
		cluster_topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (_writer == NULL) {
		printf("create_datawriter1 error\n");
		throw runtime_error("Unable to create writer1");
	}

	_turbine_writer = TurbineMessageDataWriter::narrow(_writer);
	if (_turbine_writer == NULL) {
		printf("DataWriter narrow_turbine error\n");
		throw runtime_error("Unable to create turbine_writer");
	}


	//_writer = publisher->create_datawriter(
	//	maxprod_reached_topic,
	//	DDS_DATAWRITER_QOS_DEFAULT,
	//	NULL,
	//	DDS_STATUS_MASK_NONE);
	//if (_writer == NULL) {
	//	printf("create_datawriter2 error\n");
	//	throw runtime_error("Unable to create writer2");
	//}

	//_maxProd_reached_writer = MaxProductionReachedMessageDataWriter::narrow(_writer);
	//if (_turbine_writer == NULL) {
	//	printf("DataWriter narrow_maxprod_reached error\n");
	//	throw runtime_error("Unable to create turbine_writer");
	//}
}


void DecentralizedParkPilot::calculateNewSetpoint()
{
	uint_fast32_t localSetpoint = 0;
	uint_fast32_t curProd = 0;
	uint_fast32_t maxProd = 0;
	uint_fast32_t cacheCount = 0;
	uint_fast32_t lastCycleTime = 0;

	TurbineMessageSeq turbines;
	DDS_SampleInfoSeq turbineInfos;
	DDS_ReturnCode_t retcode;
	int sample_count = 0; /* infinite loop */

	if (_reader == NULL) {
		printf("DataReader narrow error\n");
		return;
	}

	_turbine->sendSetpoint(localSetpoint);
	_turbine->readTurbineData(maxProd, curProd);

	TurbineMessage *instance = TurbineMessageTypeSupport::create_data();
	instance->turbineId = cmdArgs.id;
	DDS_InstanceHandle_t instance_handle = _turbine_writer->register_instance(*instance);

	if( !cmdArgs.silent ) {
		std::cout << endl << "DECENTRALIZED PARK PILOT" << endl;
		cout << " N    Time     ID Prod Setpoint  Max  GlobalSetpoint CycleTime(ns) CacheCount" << endl;
	}

	for (int count = 0; (sample_count == 0) || (count < sample_count); ++count) {

		instance->currentProduction = curProd;
		instance->maxProduction = maxProd;
		instance->setPoint = localSetpoint;
		instance->msSinceLastWrite = lastCycleTime;
		instance->cacheCount = cacheCount;
		

		//update timestamp
		_ms_last_write_timestamp = chrono::duration_cast<chrono::nanoseconds>(
			chrono::high_resolution_clock::now().time_since_epoch()
			);

		retcode = _turbine_writer->write(*instance, instance_handle);

		if (retcode != DDS_RETCODE_OK) {
			printf("write error %d\n", retcode);
			throw runtime_error("write error " + retcode);
		}

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

		localSetpoint = regAlgorithm(cmdArgs.setpoint, turbines, maxProd, curProd, localSetpoint, turbineInfos, cacheCount);

		_turbine->sendSetpoint(localSetpoint);
		_turbine->readTurbineData(maxProd, curProd);

		lastCycleTime = this->calculateCycleTime(turbineInfos);

		if( !cmdArgs.silent ) {
			printReceivedTurbineData(turbines, turbineInfos);
		}


		result = _reader->return_loan(turbines, turbineInfos);
		if (result != DDS_RETCODE_OK) {
			throw runtime_error("A loan return error occurred: " + result);
		}
	sleep:
		this_thread::sleep_for(chrono::milliseconds(cmdArgs.msleep));
	}
}

uint_fast32_t DecentralizedParkPilot::regAlgorithm(
	uint_fast32_t globalSetpoint,
	TurbineMessageSeq turbines,
	uint_fast32_t maxProd,
	uint_fast32_t currentProd,
	uint_fast32_t setPoint,
	DDS_SampleInfoSeq turbineInfos,
	uint_fast32_t &cacheCount )
{
	cacheCount = 0;
	if (currentProd >= maxProd)
		return maxProd;

	int availableTurbinesCount = turbines.length();

	for (int i = 0; i < turbines.length(); i++)
	{
		if (!turbineInfos[i].valid_data) {
			availableTurbinesCount--;
			continue;
		}

		if (turbineInfos[i].sample_state == DDS_READ_SAMPLE_STATE) {
			cacheCount++;
		}

		if (turbines[i].currentProduction >= turbines[i].maxProduction)
			availableTurbinesCount--;
	}
	uint_fast32_t localSetpoint = 0;

	if (availableTurbinesCount <= 0)
		localSetpoint = globalSetpoint;
	else
		localSetpoint = globalSetpoint / availableTurbinesCount;

	if (localSetpoint > maxProd) {
		localSetpoint = maxProd;
	}

	return localSetpoint;
}

uint_fast32_t DecentralizedParkPilot::calculateCycleTime(DDS_SampleInfoSeq turbineInfos){
	DDS_Time_t oldestDataMsgTs = turbineInfos[0].source_timestamp;
	ptime tStart;
	ptime tEnd(microsec_clock::universal_time());
	time_t now = time(NULL);
	time_duration td;

	for(int i = 1; i < turbineInfos.length(); i++){
		DDS_Time_t ts = turbineInfos[i].source_timestamp;
		if(ts.nanosec < oldestDataMsgTs.nanosec && ts.sec < oldestDataMsgTs.sec){
			oldestDataMsgTs = ts;
		}
	}
	tStart = from_time_t(oldestDataMsgTs.sec);
	tStart += nanoseconds(oldestDataMsgTs.nanosec);
	td = tEnd - tStart;
	return td.fractional_seconds();
}

void DecentralizedParkPilot::printReceivedTurbineData(TurbineMessageSeq turbines, DDS_SampleInfoSeq turbineInfos)
{
	uint_fast64_t CycleTimeAvgCalculation = 0;
	for (int i = 0; i < turbines.length(); ++i) {
		DDS_SampleInfo& turbineInfo = turbineInfos[i];

		if( !turbineInfo.valid_data ) {
			continue;
		}

		TurbineMessage& turbineData = turbines[i];

		if( turbineData.turbineId != this->cmdArgs.id ) {
			continue;
		}
		
		if(cycleAvgBufferIndex > CYCLE_AVG_BUFFER_SIZE){
			cycleAvgBufferIndex = 0;
		}
		cycleAvgBuffer[cycleAvgBufferIndex++] = turbineData.msSinceLastWrite;
		for(uint_fast32_t i = 0; i < CYCLE_AVG_BUFFER_SIZE; i++){
			CycleTimeAvgCalculation += cycleAvgBuffer[i];
		}
		CycleTimeAvgCalculation /= CYCLE_AVG_BUFFER_SIZE;

		cout << "\r";
		cout << setfill(' ') << setw(2) << turbines.length();

		time_t src_time = (time_t)turbineInfo.source_timestamp.sec;
		tm* local_src_time = localtime(&src_time);

		cout << " [" << std::setw(2) << std::setfill('0') << local_src_time->tm_hour
			<< ":" << std::setw(2) << std::setfill('0')
			<< local_src_time->tm_min
			<< ":" << std::setw(2) << std::setfill('0')
			<< local_src_time->tm_sec << "] ";

		cout << setfill(' ') << setw(2) << turbineData.turbineId;
		cout << setfill(' ') << setw(6) << turbineData.currentProduction;
		cout << setfill(' ') << setw(7) << turbineData.setPoint;
		cout << setfill(' ') << setw(8) << turbineData.maxProduction;
		cout << setfill(' ') << setw(10) << cmdArgs.setpoint;
		cout << "        ";
		cout << setfill('0') << setw(fractionWidth) << CycleTimeAvgCalculation;
//		cout << setfill('0') << setw(fractionWidth) << turbineData.msSinceLastWrite;
		cout << setfill(' ') << setw(9) << turbineData.cacheCount;

		//		cout << setfill('0') << setw(fractionWidth) << lastCycleTime << endl;

		std::cout.flush( );
	}
}

void DecentralizedParkPilot::productionLevelReached(long localAndMaxDiff)
{
	DDS_ReturnCode_t retcode;

	MaxProductionReachedMessage *msg = MaxProductionReachedMessageTypeSupport::create_data();
	msg->turbineId = cmdArgs.id;
	DDS_InstanceHandle_t instance_handle = _maxProd_reached_writer->register_instance(*msg);
	
	msg->localAndMaxDiff = localAndMaxDiff;

	retcode = _maxProd_reached_writer->write(*msg, instance_handle);

	if (retcode != DDS_RETCODE_OK) {
		printf("maxprod reached write error %d\n", retcode);
		throw runtime_error("maxprod reached write error " + retcode);
	}
}
