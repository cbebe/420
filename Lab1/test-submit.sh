#!/bin/sh

sub_dir=submission
zip_file=$(head -n1 members.txt).zip

echo "1" | ./submit.sh
mkdir -p $sub_dir
unzip $zip_file -d $sub_dir >/dev/null

cd ${sub_dir}/Code
make
cd -

cp ${sub_dir}/Code/main .
rm -rf $sub_dir $zip_file
make test
make d-clean
