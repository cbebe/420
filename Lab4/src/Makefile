CFLAGS := -Wall -Wextra -Wpedantic -O3
LDFLAGS := -lm

main: main.c Lab4_IO.c page_rank.c
	mpicc $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f main

.PHONY: clean
