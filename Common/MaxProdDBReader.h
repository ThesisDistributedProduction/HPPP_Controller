#pragma once
#include "Turbine\MongoDatareader.h"

class MaxProdDBReader : public iMongoDatareader {
public:

	void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) {
		this->cursor = cursor;
	}

	uint_fast32_t getNextValue( ) {
		return cursor->next( )["AvailablePower"].Int( );
	}
	
private:
	std::auto_ptr<mongo::DBClientCursor> cursor;
};
