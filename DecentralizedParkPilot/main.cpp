#include <iostream>
#include <ndds/ndds_cpp.h>
#include <list>
#include <fstream>
#include <vector>

#include "DecentralizedParkPilot.h"

using namespace std;

static bool fileExist(const char *fileName) {
	std::ifstream stream;
	stream.open(fileName);
	if( !stream ) {
		return false;
	}
	stream.close( );
	return true;
}

static bool participant_shutdown(DDSDomainParticipant *participant) {
	DDS_ReturnCode_t retcode;

	if( participant != NULL ) {
		retcode = participant->delete_contained_entities( );
		if( retcode != DDS_RETCODE_OK ) {
			printf("delete_contained_entities error %d\n", retcode);
			return false;
		}

		retcode = DDSTheParticipantFactory->delete_participant(participant);
		if( retcode != DDS_RETCODE_OK ) {
			printf("delete_participant error %d\n", retcode);
			return false;
		}
	}

	retcode = DDSDomainParticipantFactory::finalize_instance( );
	if( retcode != DDS_RETCODE_OK ) {
		printf("finalize_instance error %d\n", retcode);
		return false;
	}
	return true;
}

static bool startDecentralizedApplication(CmdArguments args) {
	DDSDomainParticipantFactory* factory = DDSDomainParticipantFactory::get_instance( );
	DDS_ReturnCode_t retcode;

	DDSDomainParticipant *participant = factory->create_participant(
		0,
		DDS_PARTICIPANT_QOS_DEFAULT,
		NULL,
		DDS_STATUS_MASK_NONE);
	if( participant == NULL ) {
		printf("create_participant error\n");
		participant_shutdown(participant);
		return false;
	}


	const char *turbine_type_name = TurbineMessageTypeSupport::get_type_name( );
	retcode = TurbineMessageTypeSupport::register_type(
		participant,
		turbine_type_name);
	if( retcode != DDS_RETCODE_OK ) {
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
	if( cluster_topic == NULL ) {
		printf("create_cluster_topic error\n");
		participant_shutdown(participant);
		return false;
	}


	const char *maxProd_reached_type_name = MaxProductionReachedMessageTypeSupport::get_type_name( );
	retcode = MaxProductionReachedMessageTypeSupport::register_type(
		participant,
		maxProd_reached_type_name);
	if( retcode != DDS_RETCODE_OK ) {
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
	if( maxProd_reached_topic == NULL ) {
		printf("create_maxProd_reached_topic error\n");
		participant_shutdown(participant);
		return false;
	}

	try {
		DecentralizedParkPilot pp(
			args,
			participant,
			cluster_topic,
			maxProd_reached_topic);

		pp.calculateNewSetpoint( );
	} catch( std::exception& ex ) {
		std::cerr << "An error occurred: " << ex.what( );
	}

	return participant_shutdown(participant);
}

int main(int argc, char *argv[], char *envp[]) {
	int main_result = 1; /* error by default */

	CmdArguments args = parseCmdLineArgs(argc, argv);

	if( !fileExist("USER_QOS_PROFILES.xml") ) {
		std::cout << "! Unable to locate QoS definition file" << std::endl;
		std::cout << "! (USER_QOS_PROFILES.xml) in current directory." << std::endl;
		return main_result;
	}

	if( startDecentralizedApplication(args) )
		main_result = 0;

	return main_result;
}
