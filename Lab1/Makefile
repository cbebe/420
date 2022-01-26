CC ?= gcc
# :^) because we're winners
CC_WARNINGS := -w
CFLAGS := $(CC_WARNINGS) -std=c90 -O3 -lpthread -lm

all: main

%: %.c lab1_IO.c
	$(CC) $^ $(CFLAGS) -o $@

# Development Makefile targets
# not included in the submission :P
test:
	$(MAKE) -f dev.mk test

clean:
	$(MAKE) -f dev.mk clean

deploy:
	$(MAKE) -f dev.mk deploy

.PHONY: all test clean deploy
