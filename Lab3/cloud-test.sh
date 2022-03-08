#!/bin/sh

[ -t 1 ] && {
    RESTORE="\033[0m"
    PURPLE="\033[01;35m"
}

exe=${EXE:-main1}

make deploy
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}# SSHing into cloud VM #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
ssh cloud "cd Lab3 && EXE=$exe make test"
printf "${PURPLE}########################${RESTORE}\n"
printf "${PURPLE}#   Exiting cloud VM   #${RESTORE}\n"
printf "${PURPLE}########################${RESTORE}\n"
