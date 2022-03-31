#!/bin/sh

# USAGE: ./do-all-gnome.sh [OUTPUT_FILE] [DO_NO_PAD]

done_beep() {
    paplay /usr/share/sounds/gnome/default/alerts/bark.ogg
}

output_file=${1:-experiment$(date +%s).txt}

ssh cloud "cd Lab4 && ./do-all.sh $output_file $2" && scp cloud:Lab4/$output_file . && done_beep
