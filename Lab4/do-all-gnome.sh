#!/bin/sh

done_beep() {
    paplay /usr/share/sounds/gnome/default/alerts/bark.ogg
}

output_file=experiment.txt

ssh cloud "cd Lab4 && ./do-all.sh $output_file" && scp cloud:Lab4/$output_file . && done_beep
