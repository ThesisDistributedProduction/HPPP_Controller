#include "ClusterListener.h"

void ClusterListener::on_data_available(DDSDataReader *reader) {
	DDSOctetsDataReader *   octet_reader = NULL;
	DDS_SampleInfo        info;
	DDS_ReturnCode_t      retcode;


	octet_reader = DDSOctetsDataReader::narrow(reader);
	if (octet_reader == NULL) {
		cerr << "DDSOctetsDataReader::narrow failed." << endl;
		return;
	}

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

			if (!isTurbineInCluster(msg.turbine.turbineId)) {
				TurbineInfo turbine = TurbineInfo(msg.turbine.turbineId);
				turbine.setCurrentProduction(msg.turbine.currentProduction);
				turbine.setMaxProduction(msg.turbine.maxProduction);
				turbine.setSetPoint(msg.turbine.setPoint);
				addTurbineToCluster(turbine);
			}

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