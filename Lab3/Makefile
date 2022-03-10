CC ?= gcc
CFLAGS := -Wall -Wpedantic -Wextra -O3

EXE ?= mainss

test: single-test.sh datagen $(EXE) serialtester
	./$< $(EXE)

main: src/main.c
	cd src && $(MAKE) $@ && cp $@ ..

main%: src/main.c src/Lab3IO.c bench/scheme%.c src/util.h
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

main00: bench/main00.c bench/scheme00.c src/Lab3IO.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

test%: bench/scheme%.c
	cd bench && $(MAKE) $@ && cp $@ ..

report: lab_report.pdf

%.pdf: %.md
	pandoc $< -o $@

%: util/%.c
	cd util && $(MAKE) $@ && cp $@ ..

clean:
	rm -f datagen main* test* serialtester speedup
	cd src && $(MAKE) $@
	cd bench && $(MAKE) $@
	cd util && $(MAKE) $@

data_clean:
	rm -f data_output times.tsv latest_times.tsv

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av . cloud:Lab3

.PHONY: test clean report deploy
