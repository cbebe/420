#!/bin/sh

code_files=src

# Prompts the user for a student ID
# in vars:
# $1 - the root directory (usually .. if called from one of the lab directories)
# out global vars:
# student_id - the student ID of the one handling the submission
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

# Creates zip file named ${student_id}.zip
# in vars:
# student_id - the student ID of the one handling the submission
# code_files - a space-separated list of files (and directories)
create_zip() {
	dirs='Code Members'
	mkdir -p $dirs
	cp -r $code_files/* Code/
	cp members.txt Members
	zip -r ${student_id}.zip $dirs >/dev/null
	rm -rf $dirs
	echo "Submission stored in $student_id.zip"
}

get_student_id
create_zip
