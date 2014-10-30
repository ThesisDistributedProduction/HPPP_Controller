
#include "Turbine.h"
#include "Turbine\MongoDatabase.h"
#include "MaxProdQuery.h"
#include "MaxProdDBReader.h"

#define DB = "turbineLog";
#define TIME_STAMP_FIELD = "TimeStamp";
#define FIXED_DATE = "2014-10-18";


using namespace std;
Turbine::Turbine(string collection) {
	auto _db = MongoDatabase::getInstance( );
	_db->setVerbose(true);
	_db->connect( );

	string startTime = "16:00:00";
	string stopTime = "17:00:00";
	MaxProdDBReader datareader;
	MaxProdQuery query(collection, startTime, stopTime);
	_db->query(query, datareader);

	cout << "max.prod: ";
	for( int i = 0; i < 10; i++ ) {
		cout << datareader.getNextValue( ) << ", ";
	}
	cout << endl;

	db = _db;

	


}