#pragma once

#include <stdint.h>

#define KW 1000		 // 1 kilowatt
#define MW KW*1000 // 1 megawatt

#define MAX_PRODUCTION_DIFF_SCALING_FACTOR 0.1

class TurbineSim {
public:

	TurbineSim(uint_fast32_t maxProduction = 2 * KW, uint_fast32_t currentProduction = 0 * KW) {
		this->maxProduction = maxProduction;
		this->currentProduction = currentProduction;
	}

	uint_fast32_t calculate(uint_fast32_t setpunkt, uint_fast32_t maxProduction) {

		// positive means more production available
		double maxProdDiff = (int_fast32_t)maxProduction - ( int_fast32_t )this->maxProduction;

		double adjustPowerMax = maxProdDiff * MAX_PRODUCTION_DIFF_SCALING_FACTOR;

		currentProduction += adjustPowerMax;

		// positive means production is above setpoint
		double powerProdDiff = (double)currentProduction - setpunkt;

		double adjustPowerProd = powerProdDiff * 0.1; //0.001;
		if( adjustPowerProd < -0.1 || adjustPowerProd > 0.1 ) {
			if( adjustPowerProd < 1 && adjustPowerProd > -1 ) {
				adjustPowerProd = ( adjustPowerProd > 0 ? 1 : -1 );
			}
			currentProduction -= adjustPowerProd;
		}
		
		//std::cout << "\nsetpunkt: " << setpunkt << "   powerDiff: " << powerDiff << " Adjustment from max Prod: " <<adjustPower << std::endl;

		this->maxProduction = maxProduction;
		if( currentProduction < 0 )
			currentProduction = 0;
		return currentProduction;
	}

private:
	//Previus values
	int_fast32_t maxProduction;
	int_fast32_t currentProduction;
};

