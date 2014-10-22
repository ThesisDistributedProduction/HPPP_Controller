// HPPP_Controller.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ndds/ndds_cpp.h>
#include <list>
#include <fstream>
#include "ClusterListener.h"
#include "ClusterSubscriber.h"

using namespace std;
DDS_Boolean shutdown_flag = DDS_BOOLEAN_FALSE;

#define MAX_STRING_SIZE 1024

static bool fileExist(const char *fileName) {
	std::ifstream stream;
	stream.open(fileName);
	if (!stream) {
		return false;
	}
	stream.close();
	return true;
}

static bool startApplication() {
	DDS_ReturnCode_t         rc;
	DDSTopic *               topic = NULL;
	bool                     returnValue = false;

	/* This example creates DDS entities using the default QoS loaded
	* from the file USER_QOS_PROFILES.xml in the current working
	* directory.
	*/
	if (!fileExist("USER_QOS_PROFILES.xml")) {
		std::cout << "! Unable to locate QoS definition file" << std::endl;
		std::cout << "! (USER_QOS_PROFILES.xml) in current directory."
			<< std::endl;
		return false;
	}
	
		
	


	DDSDomainParticipantFactory* factory =
		DDSDomainParticipantFactory::get_instance();
	/* If you need to customize any DDS factory QoS, uncomment the following
	* code:
	*
	{
	DDS_DomainParticipantFactoryQos factoryQos;
	rc = factory->get_qos(factoryQos);
	if (rc != DDS_RETCODE_OK) {
	std::cerr << "! Unable to get participant factory QoS: "
	<< rc << std::endl;
	goto exitFn;
	}

	// Modify the factory QoS here

	rc = factory->set_qos(factoryQos);
	if (rc != DDS_RETCODE_OK) {
	std::cerr << "! Unable to set participant factory QoS: "
	<< rc << std::endl;
	goto exitFn;
	}
	}
	*/


	/* Creates the DDS Domain Participant.
	* If you want to create a domain participant with different QoS,
	* use DDSDomainParticipantFactory::get_default_participant_qos
	* to obtain a copy of the default participant QoS, change them,
	* then use them instead of DDS_PARTICIPANT_QOS_DEFAULT:
	*
	{
	DDS_DomainParticipantQos myQos;
	factory->get_default_participant_qos(myQos);
	// Modify the participant QoS here
	// Then create the domain participant using 'myQos'...
	}
	*/

	DDSDomainParticipant* participant = factory->create_participant(
		0,
		DDS_PARTICIPANT_QOS_DEFAULT,
		NULL,                    // no listener
		DDS_STATUS_MASK_NONE);   // no listener callbacks
	if (participant == NULL) {
		std::cerr << "! Unable to create DomainParticipant" << std::endl;
		goto exitFn;
	}

	/* Creates the topic.
	* If you want to create a topic with different QoS,
	* use DDSDomainParticipant::get_default_topic_qos
	* to obtain a copy of the default topic QoS, change them,
	* then use them instead of DDS_TOPIC_QOS_DEFAULT:
	*
	{
	DDS_TopicQos myQos;
	participant->get_default_topic_qos(myQos);

	// Modify the topic QoS here
	// Then create the topic using 'myQos'...
	}
	*/
	topic = participant->create_topic(
		"Cluster 1",
		DDSKeyedOctetsTypeSupport::get_type_name(),
		DDS_TOPIC_QOS_DEFAULT,
		NULL,                    // no listener
		DDS_STATUS_MASK_NONE);    // no listener callbacks
	if (topic == NULL) {
		std::cerr << "! Unable to create topic" << std::endl;
		goto exitFn;
	}

	try
	{
		ClusterSubscriber sub(
			participant,
			topic);


		sub.calculateNewSetpoint();
	}
	catch (std::exception& ex) {
		std::cerr << "An error occurred: " << ex.what();
	}

exitFn:
	if (participant != NULL) {
		/* Perform a clean shutdown of the participant and all the contained
		* entities
		*/
		rc = participant->delete_contained_entities();
		if (rc != DDS_RETCODE_OK) {
			std::cerr << "! Unable to delete participant contained entities: "
				<< rc << std::endl;
		}

		rc = factory->delete_participant(participant);
		if (rc != DDS_RETCODE_OK) {
			std::cerr << "! Unable to delete participant: " << rc << std::endl;
		}
	}
	DDSDomainParticipantFactory::finalize_instance();
	return true;
}




int main() {
	int                           main_result = 1; /* error by default */
	
	if (startApplication())
		main_result = 0;

	
//	DDSDomainParticipant *        participant = NULL;
//	DDSTopic *                    topic = NULL;
//	DDSDataReader *               data_reader = NULL;
//	ClusterListener               listener;
//	DDS_ReturnCode_t              retcode;
//
//	/* --- Set Up --------------------------------------------------------- */
//
//	/* Uncomment the following lines to increase the verbosity of the log
//	* messages output by RTI Connext:
//	NDDSConfigLogger::get_instance()->set_verbosity_by_category(
//	NDDS_CONFIG_LOG_CATEGORY_API,
//	NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL );
//	*/
//
//	/* Create the domain participant on domain ID 0 */
//	participant = DDSDomainParticipantFactory::get_instance()->
//		create_participant(
//		0,                              /* Domain ID */
//		DDS_PARTICIPANT_QOS_DEFAULT,    /* QoS */
//		NULL,                           /* Listener */
//		DDS_STATUS_MASK_NONE);
//	if (participant == NULL) {
//		cerr << "Unable to create domain participant." << endl;
//		goto clean_exit;
//	}
//
//	/* Create the topic "Hello, World" for the String type */
//	topic = participant->create_topic(
//		"Cluster 1",                        /* Topic name*/
//		DDSOctetsTypeSupport::get_type_name(), /* Type name */
//		DDS_TOPIC_QOS_DEFAULT,                 /* Topic QoS */
//		NULL,                                  /* Listener  */
//		DDS_STATUS_MASK_NONE);
//	if (topic == NULL) {
//		cerr << "Unable to create topic." << endl;
//		goto clean_exit;
//	}
//
//	/* Create the data writer using the default publisher */
//	data_reader = participant->create_datareader(
//		topic,
//		DDS_DATAREADER_QOS_DEFAULT,    /* QoS */
//		&listener,                      /* Listener */
//		DDS_DATA_AVAILABLE_STATUS);
//	if (data_reader == NULL) {
//		cerr << "Unable to create data reader." << endl;
//		goto clean_exit;
//	}
//
//	/* --- Sleep During Asynchronous Reception ---------------------------- */
//
//	/* This thread sleeps forever. When a sample is received, RTI Data
//	* Distribution Service will call the on_data_available_callback function.
//	*/
//	cout << "Ready to read data." << endl;
//	cout << "Press CTRL+C to terminate." << endl;
//	for (;;) {
//#ifdef RTI_WIN32
//		Sleep(2000);
//#else
//		sleep(2);
//#endif
//		if (shutdown_flag){
//			break;
//		}
//	}
//
//	/* --- Clean Up ------------------------------------------------------- */
//
//	main_result = 0;
//clean_exit:
//	cout << "Exiting..." << endl;
//	if (participant != NULL) {
//		retcode = participant->delete_contained_entities();
//		if (retcode != DDS_RETCODE_OK) {
//			cerr << "Deletion failed." << endl;
//			main_result = 1;
//		}
//		retcode = DDSDomainParticipantFactory::get_instance()->
//			delete_participant(participant);
//		if (retcode != DDS_RETCODE_OK) {
//			cerr << "Deletion failed." << endl;
//			main_result = 1;
//		}
//	}

	return main_result;
}
