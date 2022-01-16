#!/bin/sh

# test-submit.sh
# Tests our submission file to make sure that everything passes
# To be as similar to the production env as possible, we're not using

set -e

RESTORE="\033[0m"
RED="\033[01;31m"
GREEN="\033[01;32m"
YELLOW="\033[01;33m"
BLUE="\033[01;34m"

zip_file=$(head -n1 members.txt).zip

cleanup() {
	echo "${GREEN}Cleaning up...${RESTORE}"
	rm -rf $zip_file Code Members main
	make d-clean 1>/dev/null
}

die() {
	cleanup
	exit 1
}

printf "${YELLOW}Creating submission file... ${RESTORE}"
echo "1" | ./submit.sh 1>/dev/null && {
	echo "${GREEN}creation successful.${RESTORE}"
} || {
	echo "${RED}error creating submission file.${RESTORE}"
	die
}

echo "${YELLOW}Unzipping submission file... ${RESTORE}"
unzip $zip_file 1>/dev/null

printf "${YELLOW}Testing members.txt... ${RESTORE}"
cmp members.txt Members/members.txt 1>/dev/null && {
	echo "${GREEN}members.txt matches.${RESTORE}"
} || {
	echo "${RED}members.txt does not match.${RESTORE}"
	die
}

cd Code
printf "${YELLOW}Testing submission Makefile...${RESTORE}"
make 1>/dev/null && {
	echo "${GREEN}executable creation successful.${RESTORE}"
} || {
	echo "${RED}error creating executable.${RESTORE}"
	die
}
cp main ..
cd - >/dev/null

echo "${YELLOW}Testing executable...${RESTORE}"
make -s test || die

cleanup
