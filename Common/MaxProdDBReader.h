
#include "Turbine\MongoDatareader.h"

class MaxProdDBReader : public iMongoDatareader {
public:
	MaxProdDBReader( ) {

	}

	void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) {
		this->cursor = cursor;
	}

	int getNextValue( ) {
		return cursor->next( )["AvailablePower"].Int( );
	}
	
private:
	std::auto_ptr<mongo::DBClientCursor> cursor;
};
