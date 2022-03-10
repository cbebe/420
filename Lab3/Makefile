CC ?= gcc
CFLAGS := -Wall -Wpedantic -Wextra -O3

EXE ?= mainss

test: single-test.sh datagen $(EXE) serialtester
	./$< $(EXE)

main: src/main.c
	cd src && $(MAKE) $@ && cp $@ ..

main%: src/main.c src/Lab3IO.c bench/scheme%.c src/util.h
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

test%: bench/scheme%.c
	cd bench && $(MAKE) $@ && cp $@ ..

report: lab_report.pdf

%.pdf: %.md
	pandoc $< -o $@

%: util/%.c
	cd util && $(MAKE) $@ && cp $@ ..

clean:
	rm -f data_output datagen main* test* times.tsv serialtester speedup
	cd src && $(MAKE) $@
	cd bench && $(MAKE) $@
	cd util && $(MAKE) $@

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av . cloud:Lab3

.PHONY: test clean report deploy
