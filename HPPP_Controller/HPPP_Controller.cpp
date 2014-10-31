#include <iostream>
#include <ndds/ndds_cpp.h>
#include <list>
#include <fstream>
#include <vector>

#include "DecentralizedParkPilot.h"
#include "CentralizedParkPilot.h"

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

static bool startCentralizedApplication()
{
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

	DDSTopic *request_topic = participant->create_topic(
		"Cluster 1_centralized_request",
		DDSStringTypeSupport::get_type_name(),
		DDS_TOPIC_QOS_DEFAULT,
		NULL,						
		DDS_STATUS_MASK_NONE);
	if (request_topic == NULL) {
		printf("create_topic error\n");
		participant_shutdown(participant);
		return false;
	}

	const char *type_name = TurbineMessageTypeSupport::get_type_name();
	DDS_ReturnCode_t retcode = TurbineMessageTypeSupport::register_type(
		participant,
		type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}

	DDSTopic *reply_topic = participant->create_topic(
		"Cluster 1_centralized_reply",
		type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,						//listener
		DDS_STATUS_MASK_NONE);
	if (request_topic == NULL) {
		printf("create_topic error\n");
		participant_shutdown(participant);
		return false;
	}


	try
	{
		CentralizedParkPilot pp(participant, request_topic, reply_topic);

		pp.calculateNewSetpoints();
	}
	catch (std::exception& ex) {
		std::cerr << "An error occurred: " << ex.what();
	}

	return participant_shutdown(participant);
}

static bool startDecentralizedApplication()
{
	DDSDomainParticipantFactory* factory = DDSDomainParticipantFactory::get_instance();
	DDS_ReturnCode_t retcode;

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


	const char *turbine_type_name = TurbineMessageTypeSupport::get_type_name();
	retcode = TurbineMessageTypeSupport::register_type(
		participant, 
		turbine_type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}

	DDSTopic *cluster_topic = participant->create_topic(
		"Cluster 1",
		turbine_type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,                    
		DDS_STATUS_MASK_NONE);    
	if (cluster_topic == NULL) {
		printf("create_cluster_topic error\n");
		participant_shutdown(participant);
		return false;
	}


	const char *maxProd_reached_type_name = MaxProductionReachedMessageTypeSupport::get_type_name();
	retcode = MaxProductionReachedMessageTypeSupport::register_type(
		participant,
		maxProd_reached_type_name);
	if (retcode != DDS_RETCODE_OK) {
		printf("register_type_maxProd_reached_type_name error %d\n", retcode);
		participant_shutdown(participant);
		return false;
	}
	DDSTopic *maxProd_reached_topic = participant->create_topic(
		"Cluster 1_maxProd_reached",
		maxProd_reached_type_name,
		DDS_TOPIC_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if (maxProd_reached_topic == NULL) {
		printf("create_maxProd_reached_topic error\n");
		participant_shutdown(participant);
		return false;
	}

	try
	{
		DecentralizedParkPilot pp(
			participant,
			cluster_topic,
			maxProd_reached_topic);

		pp.calculateNewSetpoint();
	}
	catch (std::exception& ex) {
		std::cerr << "An error occurred: " << ex.what();
	}

	return participant_shutdown(participant);
}

int main() {
	int main_result = 1; /* error by default */
	string collections[4] = { "Turbine3000363Log", "Turbine3000364Log", "Turbine3000365Log", "Turbine3000366Log" };
	try {
		Turbine t(collections[0]);
	} catch( exception &e) {
		cout << "exception caught while running Turbine sim, is mongo db installed and setup???\n" << endl;
	}

	if (!fileExist("USER_QOS_PROFILES.xml")) {
		std::cout << "! Unable to locate QoS definition file" << std::endl;
		std::cout << "! (USER_QOS_PROFILES.xml) in current directory." << std::endl;
		return main_result;
	}

	if (startDecentralizedApplication())
		main_result = 0;

	//if (startCentralizedApplication())
	//	main_result = 0;

	//if (startStructMessageApplication())
		//main_result = 0;

	return main_result;
}
