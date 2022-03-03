CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

test: test.sh datagen main serialtester
	./$<

%: src/%.c
	cd src && $(MAKE) $@ && cp $@ ..

%: util/%.c
	cd util && $(MAKE) $@ && cp $@ ..

.PHONY: test
