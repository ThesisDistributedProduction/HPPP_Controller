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

static bool startTurbineForCentralizedApplication(uint_fast32_t turbineId)
{
	DDS_ReturnCode_t retcode;

	DDSDomainParticipantFactory* factory = DDSDomainParticipantFactory::get_instance();

	DDSDomainParticipant *participant = factory->create_participant(
		0,
		DDS_PARTICIPANT_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (participant == NULL) {
		printf("create_participant error\n");
		participant_shutdown(participant);
		return false;
	}

	const char *req_type_name = RequestMessageTypeSupport::get_type_name();
	retcode = RequestMessageTypeSupport::register_type(
		participant,
		req_type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}

	DDSTopic *request_topic = participant->create_topic(
		"Cluster 1_centralized_request",
		req_type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,						
		DDS_STATUS_MASK_NONE);
	if (request_topic == NULL) {
		printf("create_topic error\n");
		participant_shutdown(participant);
		return false;
	}

	const char *rep_type_name = TurbineDataMessageTypeSupport::get_type_name();
	retcode = TurbineDataMessageTypeSupport::register_type(
		participant,
		rep_type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}

	DDSTopic *reply_topic = participant->create_topic(
		"Cluster 1_centralized_reply",
		rep_type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,						//listener
		DDS_STATUS_MASK_NONE);
	if (request_topic == NULL) {
		printf("create_topic error\n");
		participant_shutdown(participant);
		return false;
	}

	Turbine turbine(turbineId);

	try
	{
		TurbineCentralized tc(turbine, participant, request_topic, reply_topic);

		while (true) {
			Sleep(2000);
		}

		/*CentralizedParkPilot pp(participant, request_topic, reply_topic);

		pp.calculateNewSetpoints();*/
	}
	catch (std::exception& ex) {
		std::cerr << "An error occurred: " << ex.what();
	}

	return participant_shutdown(participant);
}

int main(int argc, char *argv[], char *envp[]){
	int main_result = 1; /* error by default */

	uint_fast32_t turbineId = 0;
	if( argc > 1 ) {
		turbineId = atoi(argv[1]);
	}

	if (!fileExist("USER_QOS_PROFILES.xml")) {
		std::cout << "! Unable to locate QoS definition file" << std::endl;
		std::cout << "! (USER_QOS_PROFILES.xml) in current directory." << std::endl;
		return main_result;
	}

	if (startTurbineForCentralizedApplication(turbineId))
		main_result = 0;

	return main_result;
}
