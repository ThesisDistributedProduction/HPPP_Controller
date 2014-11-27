#pragma once

#include <string>
#include <memory>

#include "iTurbine.h"
#include "MaxProdDBReader.h"
#include "TurbineSim.h"

class Turbine : public iTurbine {
public:
	Turbine(uint_fast32_t id);
	
	void sendSetpoint(uint_fast32_t setPoint) override;
	uint_fast32_t getSetpoint() override { return setPoint; }

	void readTurbineData(uint_fast32_t &maxProduction, uint_fast32_t &currentProduction) override;

	uint_fast32_t getTurbineId() override { return turbineId; }

private:
	TurbineSim tSim;
	MaxProdDBReader datareader;
	uint_fast32_t maxProduction;
	uint_fast32_t currentProduction;
	uint_fast32_t setPoint;
	uint_fast32_t turbineId;
};

