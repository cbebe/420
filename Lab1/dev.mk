CC ?= gcc
CFLAGS := -Wall -Wpedantic -std=c90 -DDEV -g -lpthread -lm

EXE := matrixgen serialtester main
DATA := data_input data_output

SIZE ?= 100
BOUND ?= 5
MEMBERS := $(shell cat members.txt)

test: data_input main serialtester
	./main
	./serialtester

data_input: matrixgen
	./matrixgen -s $(SIZE) -b $(BOUND)

%: %.c lab1_IO.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -f $(EXE) $(DATA) $(MEMBERS:%=%.zip)

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av . cloud:Lab1

.PHONY: clean deploy test
