#include <iostream>
#include <ndds/ndds_cpp.h>
#include <list>
#include <fstream>
#include <vector>

#include "TurbineCentralized.h"

#include "Turbine.h"

using namespace std;

static bool fileExist(const char *fileName) {
	std::ifstream stream;
	stream.open(fileName);
	if (!stream) {
		return false;
	}
	stream.close();
	return true;
}

static bool participant_shutdown(DDSDomainParticipant *participant)
{
	DDS_ReturnCode_t retcode;

	if (participant != NULL) {
		retcode = participant->delete_contained_entities();
		if (retcode != DDS_RETCODE_OK) {
			printf("delete_contained_entities error %d\n", retcode);
			return false;
		}

		retcode = DDSTheParticipantFactory->delete_participant(participant);
		if (retcode != DDS_RETCODE_OK) {
			printf("delete_participant error %d\n", retcode);
			return false;
		}
	}

	retcode = DDSDomainParticipantFactory::finalize_instance();
	if (retcode != DDS_RETCODE_OK) {
		printf("finalize_instance error %d\n", retcode);
		return false;
	}
	return true;
}

static bool startTurbineForCentralizedApplication(CmdArguments args)
{
	DDS_ReturnCode_t retcode;

	DDSDomainParticipantFactory* factory = DDSDomainParticipantFactory::get_instance();
	auto qos = DDS_PARTICIPANT_QOS_DEFAULT;
//	qos.wire_protocol.participant_id = args.id;
	DDSDomainParticipant *participant = factory->create_participant(
		0,
		qos,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (participant == NULL) {
		printf("create_participant error\n");
		participant_shutdown(participant);
		return false;
	}

	const char *setpoint_type_name = SetpointMessageTypeSupport::get_type_name();
	retcode = SetpointMessageTypeSupport::register_type(
		participant,
		setpoint_type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}

	std::string topic_name = "Cluster 1";
	//topic_name += std::to_string(turbineId);

	DDSTopic *setpoint_topic = participant->create_topic(
		topic_name.c_str(),
		setpoint_type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,						
		DDS_STATUS_MASK_NONE);
	if (setpoint_topic == NULL) {
		printf("create_topic error\n");
		participant_shutdown(participant);
		return false;
	}
	std::string contentFilterExpression = "turbineId=" + std::to_string(args.id);

	//std::string contentFilterExpression = "key='BLA'";

	const DDS_StringSeq noFilterParams;
	string cftName = string(setpoint_topic->get_name()) + string(" (filtered)");
	DDSTopicDescription* cft = participant->create_contentfilteredtopic(
		cftName.c_str(),
		setpoint_topic,
		contentFilterExpression.c_str(),
		noFilterParams);
	if (cft == NULL) {
		throw std::runtime_error("Unable to create ContentFilteredTopic");
	}

	Turbine turbine(args.id);

	try
	{
		TurbineCentralized tc(turbine, participant, cft, args);

		tc.waitForRequests();
	}
	catch (std::exception& ex) {
		std::cerr << "An error occurred: " << ex.what();
	}

	return participant_shutdown(participant);
}

int main(int argc, char *argv[], char *envp[]){
	int main_result = 1; /* error by default */

	CmdArguments args = parseCmdLineArgs(argc, argv);

	if (!fileExist("USER_QOS_PROFILES.xml")) {
		std::cout << "! Unable to locate QoS definition file" << std::endl;
		std::cout << "! (USER_QOS_PROFILES.xml) in current directory." << std::endl;
		return main_result;
	}

	if( startTurbineForCentralizedApplication(args) )
		main_result = 0;

	return main_result;
}
