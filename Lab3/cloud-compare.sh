#!/bin/sh

RESTORE="\033[0m"
PURPLE="\033[01;35m"

exe=${EXE:-main1}

make deploy
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}# SSHing into cloud VM #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
ssh cloud "cd Lab3 && ./compare.sh"
scp cloud:Lab3/times.tsv .
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}#   Exiting cloud VM   #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
