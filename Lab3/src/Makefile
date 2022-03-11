CC ?= gcc
CFLAGS := -Wall -Wpedantic -Wextra -O3

main: main.c Lab3IO.c scheme.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

clean:
	rm -f main
