#include "ClusterSubscriber.h"


ClusterSubscriber::ClusterSubscriber(
	DDSDomainParticipant* participant,
	DDSTopic* topic)
{

	/*DDSTopicDescription* topicOrContentFilteredTopic = topic;

	std::string cftName =
		std::string(topic->get_name()) + std::string(" (filtered)");
	const DDS_StringSeq noFilterParams;
	topicOrContentFilteredTopic =
		participant->create_contentfilteredtopic(
		cftName.c_str(),
		topic,
		contentFilterExpression.c_str(),
		noFilterParams);
	if (topicOrContentFilteredTopic == NULL) {
		throw std::runtime_error(
			"Unable to create ContentFilteredTopic");
	}*/

	// --- Create DataReader --- // 
	/* If you want to customize the reader QoS, use
	* DDSSubscriber::get_default_datareader_qos()
	* to initialize a local copy of the default QoS, modify them, then
	* use them in the creation call below instead of
	* DATAREADER_QOS_DEFAULT.
	*/

	//DDSDataReader* data_reader = participant->create_datareader(
	//			topic,
	//			DDS_DATAREADER_QOS_DEFAULT,    /* QoS */
	//			&listener,                      /* Listener */
	//			DDS_DATA_AVAILABLE_STATUS);

	DDSDataReader* untypedReader = participant->create_datareader(
		topic,
		DDS_DATAREADER_QOS_DEFAULT,
		NULL,             // listener
		DDS_DATA_AVAILABLE_STATUS);   // all callbacks
	if (untypedReader == NULL) {
		throw std::runtime_error("Unable to create DataReader");
	}
	/* The following narrow function should never fail, as it performs
	* only a safe cast of the generic data writer into a specific
	* DDSKeyedStringDataReader.
	*/
	_reader = DDSKeyedOctetsDataReader::narrow(untypedReader);
	if (_reader == NULL) {
		throw std::runtime_error(
			"Unable to narrow data reader into DDSKeyedStringDataReader");
	}
}


ClusterSubscriber::~ClusterSubscriber()
{
}

void ClusterSubscriber::calculateNewSetpoint()
{
	DDS_KeyedOctetsSeq turbines;
	DDS_SampleInfoSeq turbineInfos;
	time_t nowTime = 0;
	tm* lt = NULL;
	int i;

	const DDS_Long MILLIS_PER_SEC = 1000;
	/* There are three ways to be notified of new data:
	*    - Non-blocking poll (see example below)
	*    - Blocking an application thread until new data is
	*      available using a WaitSet (see other code examples)
	*    - Asynchronous notification in a middleware thread
	*      using a listener (the code below installs a listener
	*      but does not use it to read data)
	*
	* When you expect your data to arrive periodically, it may
	* be appropriate -- depending on your latency requirements --
	* to simply poll for data at that period.
	*
	* Once you know you want to get data, there are 2 ways to
	* get it:
	*    - "reading" it: View the data in the middleware's
	*      internal cache, but leave it in that cache so that
	*      you can get it back later if you want it. This is
	*      what the code below does.
	*    - "taking" it: View the data in the middleware's cache,
	*      and simultaneously remove it from that cache such
	*      that future reads/takes will not see it.
	*/
	for (int k = 0; k < 20; k++) {

		DDS_ReturnCode_t result = _reader->read(
			turbines,             // fill in data here
			turbineInfos,         // fill in parallel meta-data here
			DDS_LENGTH_UNLIMITED, // any # articles
			DDS_ANY_SAMPLE_STATE,
			DDS_ANY_VIEW_STATE,
			DDS_ANY_INSTANCE_STATE);
		if (result == DDS_RETCODE_NO_DATA) {
			// nothing to read; go back to sleep
			goto sleep;
		}
		if (result != DDS_RETCODE_OK) {
			// an error occurred: stop reading
			throw std::runtime_error("A read error occurred: " + result);
		}

		for (i = 0; i < turbines.length(); ++i) {
			DDS_SampleInfo& turbineInfo = turbineInfos[i];
			/* articles[i] contains a valid data sample; it's not
			* just a notification of a state change.
			*/
			if (!turbineInfo.valid_data) {
				continue;
			}

			// Article contents:
			DDS_KeyedOctets& turbineData = turbines[i];
			//Article article(articleData.key, articleData.value);
			// Time stamp:
			time_t src_time = (time_t)turbineInfo.source_timestamp.sec;
			tm* local_src_time = localtime(&src_time);
			// Print output:

			TurbineMessage msg;

			memset(msg.turbine.turbineId, 0, 20);

			memcpy(msg.rawMsg, turbineData.value, turbineData.length);

			printf("\n");
			std::cout
				<< "[" << local_src_time->tm_hour
				<< ":" << std::setw(2) << std::setfill('0')
				<< local_src_time->tm_min
				<< ":" << std::setw(2) << std::setfill('0')
				<< local_src_time->tm_sec << "] ";
			printf("Id: %s", turbineData.key);
			printf(" msg: %s", msg.turbine.turbineId);
			if (turbineInfo.sample_state == DDS_READ_SAMPLE_STATE) {
				// Have we seen this article before?
				std::cout << " (cached)";
			}
			/*printf("Current production: %i\n", msg.turbine.currentProduction);
			printf("Max production: %i\n", msg.turbine.maxProduction);
			printf("Set point production: %i\n", msg.turbine.setPoint);

			std::cout << std::endl;*/
		}

		/* For the sake of efficiency, we're using object pools
		* maintained by the middleware. Return the objects to the
		* pool so that the middleware can recycle them.
		*/
		result = _reader->return_loan(turbines, turbineInfos);
		if (result != DDS_RETCODE_OK) {
			// an error occurred: stop reading
			throw std::runtime_error(
				"A loan return error occurred: " + result);
		}

	sleep:
		// --- Sleep --- //
		// ...until it's time to read again.
		Sleep(150);

	}
}
