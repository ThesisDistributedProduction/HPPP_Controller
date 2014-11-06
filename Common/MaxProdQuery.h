#pragma once

#include "Turbine/MongoPrepariedQuery.h"

#include <memory>

#include <boost/date_time/posix_time/posix_time.hpp>

#include "Turbine/IncludeMongo.h"

class MaxProdQuery : public iMongoPrepairedQuery {
public:
	MaxProdQuery( std::string collection, std::string timeFrom, std::string timeTo ) {
		this->collection = collection;
		timeStampLow = MakeTime(FIXED_DATE + " " + timeFrom + ".000");
		timeStampHigh = MakeTime(FIXED_DATE + " " + timeTo + ".000");
	}

	std::auto_ptr<mongo::Query> getQuery( ) {
		mongo::BSONObj json = BSON(TIME_STAMP_FIELD << mongo::GTE << timeStampLow << mongo::LT << timeStampHigh);

		mongo::Query q(json);
		q.sort(TIME_STAMP_FIELD);

		return std::auto_ptr<mongo::Query>(new mongo::Query(q));
	}

	std::auto_ptr<mongo::BSONObj> getFilter( ) {
		auto filter = BSON("AvailablePower" << 1 << "_id" << 0);

		return std::auto_ptr<mongo::BSONObj>(new mongo::BSONObj(filter));
	}

	const std::string getCollection( ) {
		return DB + "." + collection;
	}

private:

	const std::string DB = "turbineLog";
	const std::string TIME_STAMP_FIELD = "TimeStamp";
	const std::string FIXED_DATE = "2014-10-18";


	mongo::Date_t MakeTime(std::string str) {
		boost::posix_time::ptime time(boost::posix_time::time_from_string(str));
		auto time2 = to_tm(time);
		return mongo::Date_t(mktime(&time2) * 1000);
	}

	std::string collection;
	mongo::Query query;
	mongo::Date_t timeStampLow;
	mongo::Date_t timeStampHigh;
};

