#!/bin/bash

# resident set size. can be wrong since it double calculates shared memory howerever sufficient for our experiemnt since we only have one node when testing

RUNTIME=2 #s
SAMPLE_RATE=0.1 #s

SAMPLES="$(echo "scale =0; ${RUNTIME} / ${SAMPLE_RATE}" | bc)"
#SAMPLES="$(expr ${RUNTIME} / ${SAMPLE_RATE})"

RECIVED_START="$(ifconfig wlan0 | grep -o 'bytes:[[:digit:]]*' | grep -o '[[:digit:]]*')"
RECIVED_START_SPLIT=(${RECIVED_START/// / })

for (( c=1; c<=$SAMPLES; c++ ))
#for i in {1..1000}
do
	sleep $SAMPLE_RATE

	MEMORY="$(ps -e -o rss,comm | grep Decentralized)" # | gawk '{print $1/1024 "MB"};'
	MEMORY_SPLIT=(${MEMORY/// / })

	RECIVED="$(ifconfig wlan0 | grep -o 'bytes:[[:digit:]]*' | grep -o '[[:digit:]]*')"
	RECIVED_SPLIT=(${RECIVED/// / })

	echo -n ${MEMORY_SPLIT[0]} ' '
	echo -n "$(expr ${RECIVED_SPLIT[0]} - ${RECIVED_START_SPLIT[0]})" ' '
	echo -n "$(expr ${RECIVED_SPLIT[1]} - ${RECIVED_START_SPLIT[1]})"
	echo -ne '\r'

done

echo ""