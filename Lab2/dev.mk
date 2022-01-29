CC ?= gcc
CFLAGS := -Wall -Wpedantic -std=c90 -DDEV -g -lpthread -lm

EXE := matrixgen serialtester main serial
DATA := data_input data_output

SIZE ?= 100
BOUND ?= 5
THREADS ?= 4
MEMBERS := $(shell cat members.txt)
ZIP_CONTENTS = Code/ Members/

test: new data_input main serialtester
	./main $(THREADS)
	./serialtester

data_input: matrixgen
	./matrixgen -s $(SIZE) -b $(BOUND)

%: %.c lab1_IO.c
	$(CC) $^ $(CFLAGS) -o $@

new:
	rm -f $(DATA)

clean:
	rm -rf $(EXE) $(DATA) $(MEMBERS:%=%.zip) $(ZIP_CONTENTS) *.dSYM

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av . cloud:Lab2

.PHONY: clean deploy test new
