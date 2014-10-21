

#pragma once
#include <ndds\ndds_cpp.h>
#include <iostream>
#include <vector>

#include "TurbineInfo.h"
#include "TurbineMessage.h"

using namespace std;

#define MAX_STRING_SIZE 1024

class ClusterListener : public DDSDataReaderListener {
private:
	const char* topicName;
	vector<TurbineInfo> turbines;
	bool isTurbineInCluster(string _turbineId)
	{
		for (int i = 0; i < turbines.size(); i++)
		{
			if (turbines[i].getTurbineId() == _turbineId) {
				return true;
			}
		}
		return false;
	}
	void addTurbineToCluster(TurbineInfo _turbine) { turbines.push_back(_turbine); }
	void removeTurbineFromCluster(TurbineInfo _turbine)
	{
		for (int i = 0; i++; i < turbines.size()) {
			if (turbines[i].getTurbineId() == _turbine.getTurbineId()) {
				turbines.erase(turbines.begin() + i);
				break;
			}
		}
	}

public:
	void on_data_available(DDSDataReader *reader);

};
