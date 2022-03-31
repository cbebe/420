#!/bin/sh

hosts_file="/home/$USER/hosts"
nodes="5300 13000 18789"

[ "$1" = "no-pad" ] && DEFINES=-DNO_PAD
DEFINES=$DEFINES make clean_data main datatrim

# Generate files if they don't exist
printf "Generating files...\n"
for node in $nodes
do
    file="data_input$node"
    [ -f "${file}_link" ] || [ -f "${file}_meta" ] || {
        ./datatrim -b $node -o $file
    }
done

my_ip=$(hostname -I)
for host in $(cat $hosts_file)
do
    [ "$host" != "$my_ip" ] && rsync -av . ${host}:Lab4
done

. ./test.sh
