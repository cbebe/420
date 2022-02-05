#! /bin/bash
# Run your client for 100 times
# 
# 
# Usage:
#	./test.sh
# Notes:
#	This shell script should be in the same directory as your
#	client implementation and your client should have portnumber 
#	and the number of strings in theArray as command line paramters;
#

if [ $# -lt 3 ]; then
	echo "arraySize serverIp serverPort"
	exit -1
fi

# Parameters
# This takes so damn long on Duplicates=100 (~50 seconds each test)
# test-all.sh takes ~50 seconds on Duplicates=5
# Maybe we'll do that for the final report
Duplicates=5
# Port Number
port=${3}
# The number of strings in theArray
arraysize=${1}
# IP of the server
IP=${2}

echo "Start..."
ATTEMPT=0
while [[ $ATTEMPT -ne $Duplicates ]]; do
	let ATTEMPT+=1
	echo "Attempt ${ATTEMPT} started."
	./client $arraysize $IP $port
	./attacker $arraysize $IP $port
	sleep 0.5
done
