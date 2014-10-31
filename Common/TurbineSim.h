

#include <stdint.h>

#define KW 1000		 // 1 kilowatt
#define MW KW*1000 // 1 megawatt

#define MAX_PRODUCTION_DIFF_SCALING_FACTOR 0.1

class TurbineSim {
public:

	TurbineSim(uint_fast32_t currentProduction = 1 * MW) {
		this->currentProduction = currentProduction;
	}

	uint_fast32_t calculate(uint_fast32_t setpunkt, uint_fast32_t maxProduction) {

		// positive means more production available
		auto maxProdDiff = maxProduction - this->maxProduction;

		currentProduction *= (double)maxProdDiff * MAX_PRODUCTION_DIFF_SCALING_FACTOR;

		// positive means production is above setpoint
		auto powerDiff = currentProduction - setpunkt;

		currentProduction *= (double)powerDiff * 0.5;

		return currentProduction;
	}

private:
	//Previus values
	uint_fast32_t maxProduction;
	uint_fast32_t currentProduction;
};

