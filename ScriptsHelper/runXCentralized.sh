#!/bin/bash

N=1
START=1
mSleep=20

if  [ -n "$3" ]; then
	mSleep=$3
fi

if  [ -n "$2" ]; then
	START=$2
fi

if  [ -n "$1" ]; then
	N=$(($1+START-1))
fi

killall TurbineForCentralizedParkPilot
killall CentralicedParkPilot

#cd ../CentralizedParkPilot
#./build/CentralicedParkPilot -n $N &

cd ../TurbineForCentralizedParkPilot

echo "Starting nodes form $START to start $N"

for (( i=START+1; i<=N; i++ )); do
	echo "staring with id: " $i "and mSleep: " $mSleep
	./build/TurbineForCentralizedParkPilot	-id $i -msleep $mSleep -s > /dev/null &
done

echo "starting with id: " $START "and mSleep: " $mSleep
./build/TurbineForCentralizedParkPilot -id $START -msleep $mSleep -s &

cd ..
#echo
#echo "staring instances please wait..."
#echo
#sleep 5s

#echo $(ps -a | grep DecentralizedPa | wc -l) instances are running
#echo
echo "Killing all instances"
read

killall TurbineForCentralizedParkPilot
