#pragma once

class iTurbine {
public:
	virtual void sendSetpoint(uint_fast32_t setPoint) = 0;
	virtual uint_fast32_t getSetpoint() = 0;

	virtual void readTurbineData(uint_fast32_t &maxProduction, uint_fast32_t &currentProduction) = 0;

	virtual uint_fast32_t getTurbineId() = 0;
};

std::shared_ptr<iTurbine> createTurbineInstance(uint_fast32_t id);
