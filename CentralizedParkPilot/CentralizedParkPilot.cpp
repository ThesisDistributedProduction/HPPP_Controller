#include "CentralizedParkPilot.h"

CentralizedParkPilot::CentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* setpoint_topic, CmdArguments args)
	: _requester(participant, "TurbineData")
{
	cmdArgs = args;

	DDSPublisher* publisher = participant->create_publisher(
		DDS_PUBLISHER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (publisher == NULL) {
		printf("create_publisher error\n");
		throw runtime_error("Unable to create DataPublisher");
	}

	DDSDataWriter* _writer = publisher->create_datawriter(
		setpoint_topic,
		DDS_DATAWRITER_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (_writer == NULL) {
		printf("create_datawriter error\n");
		throw runtime_error("Unable to create writer");
	}

	_setpoint_writer = SetpointMessageDataWriter::narrow(_writer);
	if (_setpoint_writer == NULL) {
		printf("DataWriter narrow error\n");
		throw runtime_error("Unable to create _setpoint_writer");
	}

	for( size_t i = 1; i < ( cmdArgs.numberOfTurbines + START_ID ); i++ )
	{
		TurbineOutlet* out = new TurbineOutlet(i, _setpoint_writer);
		out->registerTurbine();
		_turbineOutlets.push_back(out);
	}
	
	if (!cmdArgs.silent) {
		std::cout << endl << "CENTRALIZED PARK PILOT" << endl;
		std::cout << "CycleTime(ns)  N  GlobalSetpoint  GlobalProd  GlobalMax" << endl;
	}
}

void CentralizedParkPilot::calculateNewSetpoints()
{
	int sample_count = 0;
	DDS_Duration_t receive_period = { 0, 150000000 }; //150 ms

	DDS_Duration_t sleep_time = { 0, 20000000 }; //20 ms
	chrono::nanoseconds ms_last_write_timestamp = chrono::duration_cast<chrono::nanoseconds>(
		chrono::high_resolution_clock::now().time_since_epoch());

	long cycle_time = 0;

	this_thread::sleep_for(chrono::milliseconds(5000));

	for (int count = 0; (sample_count == 0) || (count < sample_count); ++count) {

		WriteSample<RequestMessage> request;


		request.data().msSinceLastWrite = (chrono::duration_cast< chrono::nanoseconds >(
			chrono::high_resolution_clock::now().time_since_epoch()) - ms_last_write_timestamp).count();

		_requester.send_request(request);


		cycle_time = request.data().msSinceLastWrite;
		

		//update timestamp
		ms_last_write_timestamp = chrono::duration_cast<chrono::nanoseconds>(
			chrono::high_resolution_clock::now().time_since_epoch()
			);

		LoanedSamples<TurbineDataMessage> replies = _requester.receive_replies(cmdArgs.numberOfTurbines, cmdArgs.numberOfTurbines, DURATION_INFINITE);

		if (replies.length() == 0) {
			//cout << "continue" << endl;
			continue;
		}


		int availableTurbinesCount = replies.length();

		typedef LoanedSamples<TurbineDataMessage>::iterator iterator;
		long localSetpoint = 0;
		long globalCurProd = 0;
		long globalMaxProd = 0;

		//regulering
		for (iterator it = replies.begin(); it != replies.end(); ++it) {
			if (it->info().valid_data) {

				if (it->data().currentProduction >= it->data().maxProduction) {
					availableTurbinesCount--;
				}

				globalCurProd += it->data().currentProduction;
				globalMaxProd += it->data().maxProduction;

				long id = it->data().turbineId;

				_turbineOutlets[it->data().turbineId - START_ID]->setCurProd(it->data().currentProduction);
				_turbineOutlets[it->data().turbineId - START_ID]->setMaxProd(it->data().maxProduction);
			}
			else
				availableTurbinesCount--;
		}
		
		if (!cmdArgs.silent) {
			std::cout << "\r";
			std::cout << setfill(' ') << setw(10) << cycle_time;
			std::cout << setfill(' ') << setw(6) << replies.length();
			std::cout << setfill(' ') << setw(11) << GLOBAL_SETPOINT;
			std::cout << setfill(' ') << setw(14) << globalCurProd;
			std::cout << setfill(' ') << setw(11) << globalMaxProd;

			std::cout.flush();
		}

		for (iterator it = replies.begin(); it != replies.end(); ++it) {
			if (it->info().valid_data) {
				if (availableTurbinesCount <= 0)
					localSetpoint = GLOBAL_SETPOINT;
				else
					localSetpoint = GLOBAL_SETPOINT / availableTurbinesCount;

				if (localSetpoint > it->data().maxProduction) {
					localSetpoint = it->data().maxProduction;
				}

				_turbineOutlets[it->data().turbineId - START_ID]->setSetpoint(localSetpoint);
				_turbineOutlets[it->data().turbineId - START_ID]->publishData();
			}
		}		


		this_thread::sleep_for(chrono::milliseconds(cmdArgs.msleep));

		/* We don't need to call replies.return_loan(); the destructor
		* takes care of doing it every time replies goes out of scope
		*/

		//printf("Centralized park pilot subscriber sleeping for %d ms...\n",
		//	(receive_period.nanosec / 1000000));

		//NDDSUtility::(receive_period);
	}
}