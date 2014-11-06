#!/bin/bash

N=$1
START=$2

if  [ -n "$1" ]; then
	N = 1
fi

if  [ -n "$2" ]; then
	START = 1
fi

cd DecentralizedParkPilot

echo "N: " $N "  start: " $START

for (( i=START; i<=N; i++ )); do
	echo "staring with id: " $i
   ../DecentralizedParkPilot_exe $i > /dev/null &
done

cd ..

ps
echo "Press any key to kill all instances"
read

killall DecentralizedParkPilot_exe