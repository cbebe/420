#!/bin/sh
# Do all experiments with all configurations
# (number of processes, single vs. multiple machines)
# This takes around 20 minutes to run, make sure to play a sound when it's done or something

output_file=${1:-experiment$(date +%s).txt}
# Truncate output file
printf "" >$output_file

run_experiment() {
    for i in  $(seq 1 4)
    do
        # Skip single process on cluster experiment
        [ "$2" != "" ] && [ "$i" = "1" ] && continue
        extra_message=$1 npes=$i do_cluster=$1 ./cloud-test.sh $2 || {
            printf "Experiment #$i with $1 failed\n" | tee -a $output_file
            continue
        }
        printf "No. of processes: $i\n" | tee -a $output_file
        rm speedup
        # Use NO_COLOR because it will be piped into a file
        gcc -O3 -DNO_COLOR devkit/speedup.c -o speedup -lm
        ./test.sh print >>$output_file
    done
    
}

date >>$output_file
printf "* With padding *\n" | tee -a $output_file
printf "*** Single Machine ***\n" | tee -a $output_file
run_experiment "With padding, Single Machine "

printf "*** Multiple Machines ***\n" | tee -a $output_file
run_experiment "With padding, Multiple Machines " 1
