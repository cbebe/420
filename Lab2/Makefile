# Development makefile
CC ?= gcc
CFLAGS := -Wall -Wpedantic -std=c90 -O3 -g -lpthread

BINS := main1 main2 main3 main4
DATA :=

MEMBERS := $(shell cat members.txt)
ZIP_CONTENTS = Code/ Members/ Report/

SRCDIR := src
OBJDIR := obj

DEPS := server operate common
SRCS := $(DEPS:%=$(SRCDIR)/%.c)
OBJS := $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

all: $(BINS)

main%: $(OBJDIR)/op%.o $(OBJS)
	$(CC) $^ $(CFLAGS) -o $@

$(OBJDIR):
	mkdir -p $@

# Lets us keep intermediate files
.SECONDARY:
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $^ $(CFLAGS) -o $@

DEVKIT_BINS := client attacker arrayRW

kit: $(DEVKIT_BINS)

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

clean:
	rm -rf $(MEMBERS:%=%.zip) $(DATA) $(ZIP_CONTENTS) $(BINS) $(DEVKIT_BINS) $(OBJDIR) *.dSYM

# Used for deploying code to our VM
# Assumes that you have configured SSH to the VM as `cloud`
deploy: clean
	rsync -av --exclude devkit . cloud:Lab2

report: lab_report.pdf

# Pandoc is pretty bloated, up to you guys if you wanna use it
%.pdf: %.md
	pandoc $< -o $@ --pdf-engine=xelatex

.PHONY: all clean deploy test report
