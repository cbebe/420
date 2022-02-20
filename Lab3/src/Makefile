CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

all: main

run: main
	./main

%: %.c Lab3IO.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^
