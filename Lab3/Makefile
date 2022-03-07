CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

test: test.sh datagen main serialtester
	./$<

main%: src/scheme%.c
	cd src && $(MAKE) $@ && cp $@ ..

%: util/%.c
	cd util && $(MAKE) $@ && cp $@ ..

.PHONY: test
