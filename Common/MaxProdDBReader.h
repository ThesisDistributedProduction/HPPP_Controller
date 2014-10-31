#pragma once
#include "Turbine\MongoDatareader.h"

class MaxProdDBReader : public iMongoDatareader {
public:

	void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) {
		this->cursor = cursor;
	}

	uint_fast32_t getNextValue( ) {
//		auto val = cursor->next( )["AvailablePower"].Int( );
		return 3000;
	}
	
private:
	std::auto_ptr<mongo::DBClientCursor> cursor;
};
