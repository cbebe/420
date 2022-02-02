#!/bin/sh

mean_file=mean-access-times

RESTORE="\033[0m"
PURPLE="\033[01;35m"

make deploy
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}# SSHing into cloud VM #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
ssh cloud "cd Lab2 && PORT=$PORT make test"
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}#   Exiting cloud VM   #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
scp cloud:Lab2/${mean_file} .
