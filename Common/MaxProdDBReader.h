#pragma once
#include "Turbine/MongoDatareader.h"
#include <chrono>
#include <thread>
#include <iostream>

class MaxProdDBReader : public iMongoDatareader {
public:

	void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) {
		this->cursor = cursor;
	}

	uint_fast32_t getNextValue( ) {
		while(!cursor->more( )){
			std::cout << "More returned false! Count = " << count << std::endl;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}
		count++;
		return cursor->next( )["AvailablePower"].Int( );
	}
	
private:
	std::auto_ptr<mongo::DBClientCursor> cursor;
	uint_fast32_t count = 0;
};
