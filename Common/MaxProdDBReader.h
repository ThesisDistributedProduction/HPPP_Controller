#pragma once
#include "Turbine/MongoDatareader.h"
#include <chrono>
#include <thread>


class MaxProdDBReader : public iMongoDatareader {
public:

	void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) {
		this->cursor = cursor;
	}

	uint_fast32_t getNextValue( ) {
		if(cursor->more( ))
			return cursor->next( )["AvailablePower"].Int( );
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if(cursor->more( ))
			return cursor->next( )["AvailablePower"].Int( );
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if(cursor->more( ))
			return cursor->next( )["AvailablePower"].Int( );
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if(cursor->more( ))
			return cursor->next( )["AvailablePower"].Int( );
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		if(cursor->more( ))
			return cursor->next( )["AvailablePower"].Int( );
		std::this_thread::sleep_for(std::chrono::milliseconds(1));

		cursor->more( );
		return cursor->next( )["AvailablePower"].Int( );

	}
	
private:
	std::auto_ptr<mongo::DBClientCursor> cursor;
};
