#!/bin/sh

npes=${npes:-2}

nodes="5300 13000 18789"

RESTORE="\033[0m"
RED="\033[01;31m"
GREEN="\033[01;32m"
YELLOW="\033[01;33m"
BLUE="\033[01;34m"

num_tests=10

set -e

make datatrim main serialtester serial average

# Generate files if they don't exist
printf "Generating files...\n"
for node in $nodes
do
    file="data_input$node"
    [ -f "${file}_link" ] || [ -f "${file}_meta" ] || {
        ./datatrim -b $node -o $file
    }
done

for node in $nodes
do
    out_file="results$node.txt"
    baseline_file="baseline$node.txt"
    rm -f data_input_meta data_input_link
    ln -s data_input${node}_meta data_input_meta
    ln -s data_input${node}_link data_input_link

    for i in $(seq 1 $num_tests)
    do
        printf "**** $node nodes -- $i of $num_tests ****\n"
        mpiexec -np $npes ./main
        awk -F: 'NR==2 {print $1; exit}' data_output >>$out_file
        ./serial
        awk -F: 'NR==2 {print $1; exit}' data_output >>$baseline_file
    done
    ./serialtester
    cat $out_file | ./average >>"average$node.txt"
    cat $baseline_file | ./average >>"average$node-serial.txt"
done
