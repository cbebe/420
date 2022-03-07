CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

EXE ?= main1

test: test.sh datagen $(EXE) serialtester
	./$< $(EXE)

main: src/main.c
	cd src && $(MAKE) $@ && cp $@ ..

main%: src/scheme%.c
	cd src && $(MAKE) $@ && cp $@ ..

%: util/%.c
	cd util && $(MAKE) $@ && cp $@ ..

clean:
	rm -f data_output datagen main* serialtester
	cd src && $(MAKE) $@

.PHONY: test clean
