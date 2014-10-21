#include <iostream>

#pragma once

using namespace std;

class TurbineInfo
{
public:
	TurbineInfo(string _turbineId);
	~TurbineInfo();

	void setMaxProduction(long _maxProduction) { maxProduction = _maxProduction; }
	long getMaxProduction() { return maxProduction; }

	void setCurrentProduction(long _currentProduction) { currentProduction = _currentProduction; }
	long getCurrentProduction() { return currentProduction; }

	void setSetPoint(long _setPoint) { setPoint = _setPoint; }
	float getSetPoint() { return setPoint; }

	string getTurbineId() { return turbineId; }
private:
	string turbineId;
	long maxProduction;
	long currentProduction;
	float setPoint;
};

