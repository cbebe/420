CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

all: main

run: main
	./main

%: src/%.c 
	cd src && $(MAKE) $@ && cp $@ ..

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

