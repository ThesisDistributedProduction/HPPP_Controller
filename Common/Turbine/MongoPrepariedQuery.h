#pragma once

#include <string>
#include <memory>


class iMongoPrepairedQuery {
public:

	virtual const std::string getCollection( ) = 0;

	virtual std::auto_ptr<mongo::Query> getQuery( ) {
		return std::auto_ptr<mongo::Query>(new mongo::Query( ));
	};

	virtual std::auto_ptr<mongo::BSONObj> getFilter( ) {
		return std::auto_ptr<mongo::BSONObj>(new mongo::BSONObj( ));
	};

};