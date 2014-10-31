#pragma once

#include <string>

#include "MaxProdDBReader.h"
#include "TurbineSim.h"
#include "TurbineMessage.h"

class Turbine {
public:
	Turbine(std::string collection);

	void sendSetpoint(uint_fast32_t setPoint);

	void readTurbineData(uint_fast32_t &maxProduction, uint_fast32_t &currentProduction);

private:
	void *db;
	TurbineSim tSim;
	MaxProdDBReader datareader;
	uint_fast32_t maxProduction;
	uint_fast32_t currentProduction;
};

