CFLAGS := -Wall -Wextra -Wpedantic -O3
# NOTE: There is a performance gain when no padding zeros are required
# However, the program will segfault when the number of nodes
# is not perfectly divisible by the number of processes
# To compile main with no padding zeros:
# DEFINES=-DNO_PAD make clean main
DEFINES := $(shell echo ${DEFINES})
LDFLAGS := -lm

main: main.c Lab4_IO.c page_rank.c
	mpicc $(CFLAGS) $(DEFINES) $^ -o $@ $(LDFLAGS)

clean:
	rm -f main

.PHONY: clean
