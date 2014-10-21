// HPPP_Controller.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <ndds/ndds_cpp.h>
#include <list>
#include "ClusterListener.h"

using namespace std;
DDS_Boolean shutdown_flag = DDS_BOOLEAN_FALSE;

#define MAX_STRING_SIZE 1024


/* The listener of events and data from the middleware */
class HelloListener : public DDSDataReaderListener {
public:
	void on_data_available(DDSDataReader *reader);
};


int main() {
	DDSDomainParticipant *        participant = NULL;
	DDSTopic *                    topic = NULL;
	DDSDataReader *               data_reader = NULL;
	ClusterListener               listener;
	DDS_ReturnCode_t              retcode;
	int                           main_result = 1; /* error by default */

	/* --- Set Up --------------------------------------------------------- */

	/* Uncomment the following lines to increase the verbosity of the log
	* messages output by RTI Connext:
	NDDSConfigLogger::get_instance()->set_verbosity_by_category(
	NDDS_CONFIG_LOG_CATEGORY_API,
	NDDS_CONFIG_LOG_VERBOSITY_STATUS_ALL );
	*/

	/* Create the domain participant on domain ID 0 */
	participant = DDSDomainParticipantFactory::get_instance()->
		create_participant(
		0,                              /* Domain ID */
		DDS_PARTICIPANT_QOS_DEFAULT,    /* QoS */
		NULL,                           /* Listener */
		DDS_STATUS_MASK_NONE);
	if (participant == NULL) {
		cerr << "Unable to create domain participant." << endl;
		goto clean_exit;
	}

	/* Create the topic "Hello, World" for the String type */
	topic = participant->create_topic(
		"Hello, World",                        /* Topic name*/
		DDSOctetsTypeSupport::get_type_name(), /* Type name */
		DDS_TOPIC_QOS_DEFAULT,                 /* Topic QoS */
		NULL,                                  /* Listener  */
		DDS_STATUS_MASK_NONE);
	if (topic == NULL) {
		cerr << "Unable to create topic." << endl;
		goto clean_exit;
	}

	/* Create the data writer using the default publisher */
	data_reader = participant->create_datareader(
		topic,
		DDS_DATAREADER_QOS_DEFAULT,    /* QoS */
		&listener,                      /* Listener */
		DDS_DATA_AVAILABLE_STATUS);
	if (data_reader == NULL) {
		cerr << "Unable to create data reader." << endl;
		goto clean_exit;
	}

	/* --- Sleep During Asynchronous Reception ---------------------------- */

	/* This thread sleeps forever. When a sample is received, RTI Data
	* Distribution Service will call the on_data_available_callback function.
	*/
	cout << "Ready to read data." << endl;
	cout << "Press CTRL+C to terminate." << endl;
	for (;;) {
#ifdef RTI_WIN32
		Sleep(2000);
#else
		sleep(2);
#endif
		if (shutdown_flag){
			break;
		}
	}

	/* --- Clean Up ------------------------------------------------------- */

	main_result = 0;
clean_exit:
	cout << "Exiting..." << endl;
	if (participant != NULL) {
		retcode = participant->delete_contained_entities();
		if (retcode != DDS_RETCODE_OK) {
			cerr << "Deletion failed." << endl;
			main_result = 1;
		}
		retcode = DDSDomainParticipantFactory::get_instance()->
			delete_participant(participant);
		if (retcode != DDS_RETCODE_OK) {
			cerr << "Deletion failed." << endl;
			main_result = 1;
		}
	}

	return main_result;
}


void HelloListener::on_data_available(DDSDataReader *reader) {
	//DDSStringDataReader * string_reader = NULL;
	DDSOctetsDataReader *   octet_reader = NULL;
	unsigned char         sample[MAX_STRING_SIZE] = { 0 };
	DDS_SampleInfo        info;
	DDS_ReturnCode_t      retcode;

	/* Perform a safe type-cast from a generic data reader into a
	* specific data reader for the type "DDS::String"
	*/
	octet_reader = DDSOctetsDataReader::narrow(reader);
	if (octet_reader == NULL) {
		/* In this specific case, this will never fail */
		cerr << "DDSStringDataReader::narrow failed." << endl;
		return;
	}

	/* Loop until there are messages available in the queue */
	for (;;) {
		DDS_Octets octets;
		retcode = octet_reader->take_next_sample(
			octets,
			info);
		if (retcode == DDS_RETCODE_NO_DATA) {
			/* No more samples */
			break;
		}
		else if (retcode != DDS_RETCODE_OK) {
			cerr << "Unable to take data from data reader, error "
				<< retcode << endl;
			return;
		}
		if (info.valid_data) {
			// Valid (this isn't just a lifecycle sample): print it

			TurbineMessage msg;

			memset(msg.turbine.turbineId, 0, 20);

			memcpy(msg.rawMsg, octets.value, octets.length);

			printf("\n");
			printf("Id: %s\n", msg.turbine.turbineId);
			printf("Current production: %i\n", msg.turbine.currentProduction);
			printf("Max production: %i\n", msg.turbine.maxProduction);
			printf("Set point production: %i\n", msg.turbine.setPoint);

			//cout << sample << endl;
			//if(strlen(sample) == 0){
			//    shutdown_flag = DDS_BOOLEAN_TRUE;
			//}
		}
	}
}