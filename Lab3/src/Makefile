CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

all: main1

run: main1
	./main1

main%: main.c Lab3IO.c scheme%.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^
