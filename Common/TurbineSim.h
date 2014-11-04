

#include <stdint.h>

#define KW 1000		 // 1 kilowatt
#define MW KW*1000 // 1 megawatt

#define MAX_PRODUCTION_DIFF_SCALING_FACTOR 0.15

class TurbineSim {
public:

	TurbineSim(uint_fast32_t maxProduction = 2 * KW, uint_fast32_t currentProduction = 1 * KW) {
		this->maxProduction = maxProduction;
		this->currentProduction = currentProduction;
	}

	uint_fast32_t calculate(uint_fast32_t setpunkt, uint_fast32_t maxProduction) {

		// positive means more production available
		double maxProdDiff = (int_fast32_t)maxProduction - ( int_fast32_t )this->maxProduction;

		double adjustPower = maxProdDiff * MAX_PRODUCTION_DIFF_SCALING_FACTOR;

		currentProduction += adjustPower;

		// positive means production is above setpoint
		double powerDiff = (double)currentProduction - setpunkt;

		currentProduction += powerDiff * 0.01;
		
		//std::cout << "\nsetpunkt: " << setpunkt << "   powerDiff: " << powerDiff << " Adjustment from max Prod: " <<adjustPower << std::endl;

		this->maxProduction = maxProduction;
		return currentProduction;
	}

private:
	//Previus values
	uint_fast32_t maxProduction;
	uint_fast32_t currentProduction;
};

