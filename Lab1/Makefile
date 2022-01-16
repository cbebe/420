CC ?= gcc
CFLAGS := -Wall -Wpedantic -std=c90

all: main

%: %.c lab1_IO.c
	$(CC) $^ $(CFLAGS) -o $@

test:
	$(MAKE) -f dev.mk test

# wildcard target for calling targets in development Makefile
# not included in submission :P
d-%:
	$(MAKE) -f dev.mk $*

clean:
	rm -f main

.PHONY: all clean