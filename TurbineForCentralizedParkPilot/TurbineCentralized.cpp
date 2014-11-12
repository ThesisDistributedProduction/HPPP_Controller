#include "TurbineCentralized.h"

SetpointListener::SetpointListener(Turbine& turbine)
{
	this->_turbine = &turbine;
}

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


TurbineCentralized::TurbineCentralized(Turbine& turbine, DDSDomainParticipant* participant, DDSTopicDescription* cft_setpoint_topic)
	: _setpoint_listener(turbine), _replier(participant, "TurbineData") //,_request_listener(turbine)
{
	this->_turbine = &turbine;
	this->_turbine->sendSetpoint(0);

	//SimpleReplierParams<RequestMessage, TurbineDataMessage>replier_params(participant,_request_listener);

	//replier_params.service_name("TurbineData");
	//replier_params.request_topic_name("TurbineDataReply");
	//replier_params.reply_topic_name("TurbineDataRequest");
	//replier_params.qos_profile("Turbine_Library", "Turbine_Profile");

	//SimpleReplier < RequestMessage, TurbineDataMessage> replier(replier_params);

	DDSDataReader* untypedReader = participant->create_datareader(
		cft_setpoint_topic,
		DDS_DATAREADER_QOS_DEFAULT,
		&_setpoint_listener,
		DDS_STATUS_MASK_ALL);			//(DDS_DATA_AVAILABLE_STATUS)
	if (untypedReader == NULL) {
		printf("create_datareader error\n");
		throw runtime_error("Unable to create DataReader");
	}

	SetpointMessageDataReader* _reader = SetpointMessageDataReader::narrow(untypedReader);
	if (_reader == NULL) {
		throw runtime_error("Unable to narrow data reader into TurbineMessageDataReader");
	}

}