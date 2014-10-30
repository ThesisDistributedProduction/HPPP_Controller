#pragma once

#include <cstddef>

#include <string>

#include "IncludeMongo.h"

#include "MongoDatareader.h"
#include "MongoPrepariedQuery.h"


class MongoDatabase {
public:
	
	static MongoDatabase *getInstance( );
	static void setVerbose( bool value );

	void connect(std::string connectionString = "localhost");
	void query(iMongoPrepairedQuery &query, iMongoDatareader &reader);

private:

	static mongo::DBClientConnection db;
	static MongoDatabase *instance;
	static bool isVerbose;

	MongoDatabase( );

};

