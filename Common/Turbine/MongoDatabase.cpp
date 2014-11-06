#include "MongoDatabase.h"

using namespace mongo;
using namespace std;

DBClientConnection MongoDatabase::db;
MongoDatabase *MongoDatabase::instance = NULL;
bool MongoDatabase::isVerbose = false;

MongoDatabase *MongoDatabase::getInstance( ) {
	if( instance == NULL ) {
		instance = new MongoDatabase( );
	}

	return instance;
}

void MongoDatabase::setVerbose(bool value) {
	isVerbose = value;
}

MongoDatabase::MongoDatabase( ) {
	mongo::client::initialize( );
}

void MongoDatabase::connect(string connectionString) {
	db.connect(connectionString);

	if( isVerbose ) {
		cout << "Connecting to database: " << connectionString << endl;
	}
}

void MongoDatabase::query(iMongoPrepairedQuery &query, iMongoDatareader &reader) {
	if( isVerbose ) {
		if( query.getCollection( ).find('.') == string::npos ) {
			throw runtime_error("MongoDatabase.h: getCollection function returns a invalid collection specification.");
		}
		cout << "quering " << query.getCollection( ) <<" with:" << query.getQuery( )->toString( ) << endl;
		cout << "Filter: " << query.getFilter( )->toString( ) << endl;
	}

	auto cursor = db.query(query.getCollection( ), *query.getQuery( ));//, 0, 0, query.getFilter().get());
	reader.giveDataCursor(cursor);
}

