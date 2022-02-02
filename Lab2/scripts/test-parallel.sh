#!/bin/bash
# WARNING: This is really unstable and resource-heavy
# You're better off running the tests serially to have more accurate results

port_num=${PORT:-3000}
host=127.0.0.1

run_test() {
  scheme=$1
  n=$2
  read < <(./main${scheme} $n $host $port_num & echo $!)
  sleep 0.5
  pid=$REPLY
  ./scripts/test.sh $n $host $port_num >/dev/null

  mean_access_time=$(./mean output-scheme${scheme}-${n})
  printf "$scheme,$n,$mean_access_time\n" >> $mean_file
  kill $pid
}

total_start=$EPOCHREALTIME
echo $total_start
run_test 1 10 & >/dev/null
port_num=$(($port_num + 1))
run_test 1 100 & >/dev/null
port_num=$(($port_num + 1))
run_test 1 1000 & >/dev/null
port_num=$(($port_num + 1))
run_test 2 10 & >/dev/null
port_num=$(($port_num + 1))
run_test 2 100 & >/dev/null
port_num=$(($port_num + 1))
run_test 2 1000 & >/dev/null
port_num=$(($port_num + 1))
run_test 3 10 & >/dev/null
port_num=$(($port_num + 1))
run_test 3 100 & >/dev/null
port_num=$(($port_num + 1))
run_test 3 1000 & >/dev/null
port_num=$(($port_num + 1))
run_test 4 10 & >/dev/null
port_num=$(($port_num + 1))
run_test 4 100 & >/dev/null
port_num=$(($port_num + 1))
run_test 4 1000 & >/dev/null
wait
total_end=$EPOCHREALTIME
echo $total_end
echo "Whole test lasted for $(awk "BEGIN{print $total_end-$total_start}") seconds"
