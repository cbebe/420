#!/bin/sh

# test-submit.sh
# Tests our submission file to make sure that everything passes
# To be as similar to the production env as possible,
# we're not defining DEV in the main executable so no pretty printing :(

set -e

old_pwd=$(pwd)

RESTORE="\033[0m"
RED="\033[01;31m"
GREEN="\033[01;32m"
YELLOW="\033[01;33m"
BLUE="\033[01;34m"

zip_file=$(head -n1 members.txt).zip

cleanup() {
	cd $old_pwd
	printf "${GREEN}Cleaning up...${RESTORE}\n"
	rm -rf $zip_file Code Members Report
	make clean 1>/dev/null
}

die() {
	cleanup
	exit 1
}

printf "${YELLOW}Creating submission file... ${RESTORE}"
echo "1" | ./scripts/submit.sh 1>/dev/null && {
	printf "${GREEN}creation successful.${RESTORE}\n"
} || {
	printf "${RED}error creating submission file.${RESTORE}\n"
	die
}

printf "${YELLOW}Unzipping submission file... ${RESTORE}\n"
unzip $zip_file 1>/dev/null

printf "${YELLOW}Testing members.txt... ${RESTORE}"
cmp members.txt Members/members.txt 1>/dev/null && {
	printf "${GREEN}members.txt matches.${RESTORE}\n"
} || {
	printf "${RED}members.txt does not match.${RESTORE}\n"
	die
}

cd Code
printf "${YELLOW}Testing submission Makefile...${RESTORE}\n"
make 1>/dev/null && {
	printf "${GREEN}executable creation successful.${RESTORE}\n"
} || {
	printf "${RED}error creating executable.${RESTORE}\n"
	die
}
# cp main ..

# printf "${YELLOW}Testing executable...${RESTORE}\n"
# SIZE=${SIZE:-100} BOUND=${BOUND:-5} THREADS=${THREADS:-4} make -f dev.mk test || die

cleanup
