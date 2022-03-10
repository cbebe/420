#!/bin/sh

size=1000
output=times.tsv
latest_output=latest_times.tsv
schemes=$(cd bench && ls scheme*)
rows=0
thread_cases="1 2 3 4 5"

make clean

# Create data_input if not present
[ -f data_input ] || {
    printf "*** Generating input data of size $size... ***\n"
    make datagen
    ./datagen -s $size
}

get_exe() {
    echo "main$1"
}

get_scheme() {
    echo $1 | sed -E 's/scheme([^.]+).c/\1/'
}

printf "*** Compiling all executables... ***\n"

for i in $schemes
do
    make $(get_exe $(get_scheme $i))
done

printf "*** Testing all schemes with multiple number of threads... ***\n"

make serialtester

for i in $schemes
do
    scheme=$(get_scheme $i)
    exe=$(get_exe $scheme)
    rows=0
    for threads in $thread_cases
    do
        rows=$(($rows + 1))
        printf "Testing $exe with $threads threads... "
        rm -f data_output
        ./$exe $threads
        [ -f data_output ] && {
            ./serialtester
            printf "$scheme\t$(tail -n1 data_output)\t$threads\n" >>$output
        } || {
            printf "$scheme\tinvalid \t$threads\n" >>$output
        }
    done
done

printf "\n" >>$output

tail -n $(((rows * 10) + 1 )) $output > $latest_output
make speedup
./speedup
