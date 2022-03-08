#!/bin/sh

size=500
num_threads=${2:-4}

[ -t 1 ] && {
	RESTORE="\033[0m"
	RED="\033[01;31m"
	GREEN="\033[01;32m"
	YELLOW="\033[01;33m"
	BLUE="\033[01;34m"
}

[ -f "data_input" ] || {
	printf "[${GREEN}DATAGEN${RESTORE}] Generating data with matrix of size $size...\n"
	./datagen -s $size
}
printf "\n[${BLUE}MAIN${RESTORE}] Solving system of equations using $num_threads threads...\n"
./$1 $num_threads
printf "\n[${YELLOW}SERIALTESTER${RESTORE}] Verifying solution...\n"
./serialtester
