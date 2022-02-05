# Development makefile
CC ?= gcc
CFLAGS := -Wall -Wpedantic -O3

BINS := main1 main2 main3 main4
DATA := output-scheme*

MEMBERS := $(shell cat members.txt)
ZIP_CONTENTS = Code/ Members/ Report/

SRCDIR := src

DEPS := server operate common read_write_lock
SRCS := $(DEPS:%=$(SRCDIR)/%.c)

all: $(BINS)

main%: $(SRCDIR)/scheme%.c $(SRCS)
	cd src && $(MAKE) $@ && cp $@ ..

mean: $(SRCDIR)/mean.c
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
	rm -rf $(MEMBERS:%=%.zip) $(DATA) $(ZIP_CONTENTS) $(BINS) $(DEVKIT_BINS) *.dSYM

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av . cloud:Lab2

report: lab_report.pdf

# Pandoc is pretty bloated, up to you guys if you wanna use it
%.pdf: %.md
	pandoc $< -o $@ --pdf-engine=xelatex

.PHONY: all clean deploy test report
