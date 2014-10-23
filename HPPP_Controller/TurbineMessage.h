#pragma once

#define MAX_TURBINEID_NAME_SIZE 20

struct TurbineStruct
{
	char turbineId[MAX_TURBINEID_NAME_SIZE];
	__int32 maxProduction;
	__int32 currentProduction;
	__int32 setPoint;
};

union TurbineMessage
{
	unsigned char rawMsg[sizeof(TurbineStruct)];
	TurbineStruct turbine;
};
