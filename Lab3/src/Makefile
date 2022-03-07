CC ?= gcc
# Don't bug us about C90!!
CFLAGS := -Wall -O3

all: main

run: main
	./main

main: main.c Lab3IO.c schemess.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

main%: main.c Lab3IO.c scheme%.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

clean:
	rm -f main main1 main2 main3 main4
