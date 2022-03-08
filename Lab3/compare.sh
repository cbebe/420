#!/bin/sh


threads=4
output=times.tsv
schemes=$(cd bench && ls scheme*)

get_scheme() {
    echo $1 | sed -E 's/scheme([^.]+).c/\1/'
}

printf "*** Compiling all executables... ***\n"

for i in $schemes
do
    exe=test$(get_scheme $i)
    make $exe
done

printf "*** Testing all schemes with $threads threads... ***\n"

for i in $schemes
do
    scheme=$(get_scheme $i)
    exe=test${scheme}
    printf "Testing $exe... "
    ./$exe $threads
    printf "$scheme\t$(tail -n1 data_output)\n" >>$output
done

printf "\n" >>$output
