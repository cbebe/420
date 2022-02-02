#!/bin/bash

port_num=${PORT:-3000}
host=127.0.0.1
mean_file=mean-access-times

run_test() {
  scheme=$1
  n=$2
  echo "Starting test with scheme $1 n=$2"
  start=$EPOCHREALTIME
  read < <(./main${scheme} $n $host $port_num & echo $!)
  sleep 0.5
  pid=$REPLY
  echo main${scheme} running on $pid
  ./scripts/test.sh $n $host $port_num
  end=$EPOCHREALTIME
  echo "Test lasted for $(awk "BEGIN{print $end-$start}") seconds"

  mean_access_time=$(./mean output-scheme${scheme}-${n})
  echo "Mean access time: $mean_access_time seconds"
  printf "$scheme,$n,$mean_access_time\n" >> $mean_file

  port_num=$(($port_num + 1))

  kill $pid
}

printf "" > $mean_file

total_start=$EPOCHREALTIME
run_test 1 10
run_test 1 100
run_test 1 1000
run_test 2 10
run_test 2 100
run_test 2 1000
run_test 3 10
run_test 3 100
run_test 3 1000
run_test 4 10
run_test 4 100
run_test 4 1000
total_stop=$EPOCHREALTIME

echo "Whole test lasted for $(awk "BEGIN{print $total_stop-$total_start}") seconds"