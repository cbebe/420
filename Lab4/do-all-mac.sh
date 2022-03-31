#!/bin/sh

# https://superuser.com/questions/598783/play-sound-on-mac-terminal
done_beep() {
    # I am not sure if this works
    afplay /System/Library/Sounds/Funk.aiff
}

output_file=experiment.txt

ssh cloud "cd Lab4 && ./do-all.sh $output_file" && scp cloud:Lab4/$output_file . && done_beep
