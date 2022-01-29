#!/bin/sh

RESTORE="\033[0m"
PURPLE="\033[01;35m"

make -f dev.mk deploy
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}# SSHing into cloud VM #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
ssh cloud "cd Lab2 && SIZE=${SIZE} BOUND=${BOUND} THREADS=${THREADS} ./test-submit.sh"
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}#   Exiting cloud VM   #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
