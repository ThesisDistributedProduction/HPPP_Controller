#include <iostream>
#include <ndds/ndds_cpp.h>
#include <list>
#include <fstream>
#include <vector>

#include "CentralizedParkPilot.h"

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

static bool startCentralizedApplication(uint_fast32_t number_of_turbines)
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

	const char *set_type_name = SetpointMessageTypeSupport::get_type_name();
	retcode = SetpointMessageTypeSupport::register_type(
		participant,
		set_type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}

	DDSTopic *setpoint_topic = participant->create_topic(
		"Cluster 1_Turbine 0",
		set_type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,						//listener
		DDS_STATUS_MASK_NONE);
	if (setpoint_topic == NULL) {
		printf("create_topic error\n");
		participant_shutdown(participant);
		return false;
	}


	try
	{
		CentralizedParkPilot pp(participant, setpoint_topic, number_of_turbines);

		pp.calculateNewSetpoints();
	}
	catch (std::exception& ex) {
		std::cerr << "An error occurred: " << ex.what();
	}

	return participant_shutdown(participant);
}

int main(int argc, char *argv[], char *envp[]){
	int main_result = 1; /* error by default */

	uint_fast32_t number_of_turbines = 0;
	if( argc > 1 ) {
		number_of_turbines = atoi(argv[1]);
	}

	if (!fileExist("USER_QOS_PROFILES.xml")) {
		std::cout << "! Unable to locate QoS definition file" << std::endl;
		std::cout << "! (USER_QOS_PROFILES.xml) in current directory." << std::endl;
		return main_result;
	}

	if (startCentralizedApplication(number_of_turbines))
		main_result = 0;

	return main_result;
}
