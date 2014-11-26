
#include "Turbine.h"
#include "Turbine/MongoDatabase.h"
#include "MaxProdQuery.h"
#include "MaxProdDBReader.h"

#define DB = "turbineLog";
#define TIME_STAMP_FIELD = "TimeStamp";
#define FIXED_DATE = "2014-10-18";

using namespace std;

shared_ptr<iTurbine> createTurbineInstance(uint_fast32_t id){
	Turbine *turbine = new Turbine(id);
	iTurbine *turbineInterface = dynamic_cast<iTurbine*>(turbine);
	shared_ptr<iTurbine> ptr(turbineInterface);
	return ptr;
};

Turbine::Turbine(uint_fast32_t id) {
	this->turbineId = id;
	auto _db = MongoDatabase::getInstance( );
	//_db->setVerbose(true);
	_db->connect( );

	string startTime = "16:00:00";
	string stopTime = "20:00:00";
		
	string collections[4] = { "Turbine3000363Log", "Turbine3000364Log", "Turbine3000365Log", "Turbine3000366Log" };

	MaxProdQuery query(collections[ id % 4], startTime, stopTime);
	_db->query(query, datareader);

	//cout << "max.prod: ";
	//for( int i = 0; i < 10; i++ ) {
	//	cout << datareader.getNextValue( ) << ", ";
	//}
	//cout << endl;

	//db = _db;
}

void Turbine::sendSetpoint(uint_fast32_t setPoint) {
	this->setPoint = setPoint;
	maxProduction = datareader.getNextValue( );
	currentProduction = tSim.calculate(setPoint, maxProduction);
}

void Turbine::readTurbineData(uint_fast32_t &maxProduction, uint_fast32_t &currentProduction) {
	maxProduction = this->maxProduction;
	currentProduction = this->currentProduction;
}
