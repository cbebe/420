#!/bin/sh

# USAGE: ./do-all-gnome.sh [OUTPUT_FILE]

# https://superuser.com/questions/598783/play-sound-on-mac-terminal
done_beep() {
    # I am not sure if this works
    afplay /System/Library/Sounds/Funk.aiff
}

output_file=${1:-experiment$(date +%s).txt}

ssh cloud "cd Lab4 && ./do-all.sh $output_file $2" && scp cloud:Lab4/$output_file . && done_beep
