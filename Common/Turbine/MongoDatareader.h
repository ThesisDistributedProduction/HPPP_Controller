#pragma once
#include <memory>

#include "IncludeMongo.h"

class iMongoDatareader {
public:

	virtual void giveDataCursor(std::auto_ptr<mongo::DBClientCursor> cursor) {
		std::cout << "iMongoDatareader.giveDataCursor() not implemented!" << std::endl;
		if( cursor->more( ) ) {
			auto count = cursor->itcount( );
			std::cout << "Cursor contained " << count << " object(s)." << std::endl;
		} else {
			std::cout << "Cursor is empty." << std::endl;
		}
	};

};