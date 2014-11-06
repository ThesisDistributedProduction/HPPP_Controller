#include "CentralizedParkPilot.h"

CentralizedParkPilot::CentralizedParkPilot(DDSDomainParticipant* participant, DDSTopic* setpoint_topic, uint_fast32_t number_of_turbines)
	: _requester(participant, "TurbineData")
{
	this->_number_of_turbines = number_of_turbines;
	/* Create the requester with the participant, and a QoS profile
	* defined in USER_QOS_PROFILES.xml
	*/
	/*connext::RequesterParams requester_params(participant);
	requester_params.service_name("PrimeCalculator");
	requester_params.qos_profile(
		"RequestReplyExampleProfiles", "RequesterExampleProfile");

    connext::Requester<PrimeNumberRequest, PrimeNumberReply> requester(
            requester_params);
	*/

	/* In this example we create the requester on the stack, but you
	* can create on the heap as well
	*/



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
}

CentralizedParkPilot::~CentralizedParkPilot()
{
}

void CentralizedParkPilot::calculateNewSetpoints()
{
	int sample_count = 0;
	DDS_Duration_t receive_period = { 0, 150000000 }; //150 ms
	DDS_Duration_t sleep_time = { 0, 10000000 }; //10 ms
	chrono::milliseconds ms_last_write_timestamp = chrono::duration_cast<chrono::milliseconds>(
		chrono::high_resolution_clock::now().time_since_epoch());

	WriteSample<RequestMessage> request;

	for (int count = 0; (sample_count == 0) || (count < sample_count); ++count) {

		request.data().msSinceLastWrite = (chrono::duration_cast< chrono::milliseconds >(
			chrono::high_resolution_clock::now().time_since_epoch()) - ms_last_write_timestamp).count();

		_requester.send_request(request);
		//update timestamp
		ms_last_write_timestamp = chrono::duration_cast<chrono::milliseconds>(
			chrono::high_resolution_clock::now().time_since_epoch()
			);

		/* Receive replies */
		const DDS::Duration_t MAX_WAIT = { 20, 0 };

		bool in_progress = true;
		while (in_progress) {
			LoanedSamples<TurbineDataMessage> replies = _requester.receive_replies(this->_number_of_turbines, this->_number_of_turbines, MAX_WAIT);

			/* When receive_replies times out,
			* it returns an empty reply collection
			*/
			if (replies.length() == 0) {
				throw std::runtime_error("Timed out waiting for replies");
				return;
			}

			/* Print the prime numbers we receive */
			typedef LoanedSamples<TurbineDataMessage>::iterator iterator;
			for (iterator it = replies.begin(); it != replies.end(); ++it) {
				if (it->info().valid_data) {

					//regulering



				}
			}

			/* We don't need to call replies.return_loan(); the destructor
			* takes care of doing it every time replies goes out of scope
			*/
		}

		printf("Centralized park pilot subscriber sleeping for %d ms...\n",
			(receive_period.nanosec / 1000000));

		NDDSUtility::sleep(receive_period);
	}
}
