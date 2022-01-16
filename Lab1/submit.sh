#!/bin/sh

code_files='main.c lab1_IO.c lab1_IO.h Makefile'

get_student_id() {
	set -- $(cat members.txt)
	# wc -l does NOT count lines.
	# https://stackoverflow.com/a/59573533
	id_count=$(grep -c ^ members.txt)
	for i in $(seq $id_count); do
		echo "$i:" $(eval echo "\$$i")
	done
	printf "Who is handling the lab submission? 🥴 [(1-$id_count), default=1]: "
	read choice
	choice=${choice:-1}
	[ $choice -gt 0 ] && [ $choice -le $id_count ] || choice=1
	student_id=$(eval echo "\$$choice")
}

get_student_id

mkdir -p Code Members
cp $code_files Code
cp members.txt Members
zip -r ${student_id}.zip Code Members >/dev/null
rm -rf Code Members
echo "Submission stored in $student_id.zip"
