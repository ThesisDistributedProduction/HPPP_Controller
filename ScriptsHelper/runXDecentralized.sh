#!/bin/bash

N=1
START=1
mSleep=20

if  [ -n "$3" ]; then
	START=$3
fi

if  [ -n "$2" ]; then
	START=$2
fi

if  [ -n "$1" ]; then
	N=$(($1+START-1))
fi

cd ../DecentralizedParkPilot

echo "Starting nodes form $START to start $N"

for (( i=START; i<=N; i++ )); do
	echo "staring with id: " $i
   build/DecentralizedParkPilot -id $i -msleep $mSleep -s &
done


cd ..
#echo
#echo "staring instances please wait..."
#echo
#sleep 5s

#echo $(ps -a | grep DecentralizedPa | wc -l) instances are running
#echo
#echo "Press any key to kill all instances"
#read

#killall DecentralizedParkPilot