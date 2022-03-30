#!/bin/sh

npes=${npes:-2}
cluster_hostname=cluster-111.novalocal

nodes=${nodes:-"5300 13000 18789"}
# nodes="5300 7000 10000"

[ "$(hostname)" = $cluster_hostname ] && hosts="-f /home/$USER/hosts"

RESTORE="\033[0m"
RED="\033[01;31m"
GREEN="\033[01;32m"
YELLOW="\033[01;33m"
BLUE="\033[01;34m"

print_speedup() {
    printf -- '+-------+--------+----------+---------+\n'
    printf    "| Nodes | Serial | Parallel | Speedup |\n"
    printf    "+-------+--------+----------+---------+\n"
    for node in $nodes
    do
        num_nodes=$(head -n1 data_input${node}_meta)
        ./speedup $num_nodes $(tail -n1 average$node-serial.txt) $(tail -n1 average$node.txt)
    done
    printf -- '+-------+--------+----------+---------+\n'
}

link_new() {
    node=$1

    rm -f data_input_meta data_input_link
    ln -s data_input${node}_meta data_input_meta
    ln -s data_input${node}_link data_input_link

    [ "$do_cluster" != "" ] && {
        printf "${RED}Copying symlinks to cluster...${RESTORE}\n"
        for host in $(cat $hosts_file)
        do
            [ "$host" != "$my_ip" ] && rsync -av . ${host}:Lab4
        done
    }
}

[ "$1" = "print" ] && print_speedup && exit 0

num_tests=10

set -e

make datatrim main serialtester serial average speedup

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
    link_new $node
    num_nodes=$(head -n1 data_input${node}_meta)

    for i in $(seq 1 $num_tests)
    do
        printf "${GREEN}**** $num_nodes nodes -- $i of $num_tests ****\n${RESTORE}"
        mpiexec $hosts -np $npes ./main
        awk -F: 'NR==2 {print $1; exit}' data_output >>$out_file
        ./serial
        awk -F: 'NR==2 {print $1; exit}' data_output >>$baseline_file
    done
    ./serialtester
    cat $out_file | ./average >>"average$node.txt"
    cat $baseline_file | ./average >>"average$node-serial.txt"
done

print_speedup
