# Development makefile
CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

BINS := main1 main2 main3 main4
UTIL_BINS := mean min
DATA := output-scheme*

MEMBERS := $(shell cat members.txt)
ZIP_CONTENTS = Code/ Members/ Report/

SRCDIR := src
UTILDIR := util

DEPS := server operate common read_write_lock
SRCS := $(DEPS:%=$(SRCDIR)/%.c)

all: $(BINS)

util: $(UTIL_BINS)

main%: $(SRCDIR)/scheme%.c $(SRCS)
	cd src && $(MAKE) $@ && cp $@ ..

%: $(UTILDIR)/%.c
	$(CC) $(CFLAGS) -o $@ $<

test: $(BINS) client mean
	PORT=$(PORT) ./scripts/test-all.sh

DEVKIT_BINS := client attacker arrayRW

kit: $(DEVKIT_BINS)

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

clean:
	cd devkit && $(MAKE) clean
	cd src && $(MAKE) clean
	rm -rf $(MEMBERS:%=%.zip) $(DATA) $(ZIP_CONTENTS) $(BINS) $(UTIL_BINS) $(DEVKIT_BINS) *.dSYM

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av . cloud:Lab2

submit: clean
	./scripts/submit.sh

report: lab_report.pdf

# Pandoc is pretty bloated, up to you guys if you wanna use it
%.pdf: %.md
	pandoc $< -o $@

.PHONY: all clean deploy test report
