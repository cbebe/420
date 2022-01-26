CC ?= gcc
CC_WARNINGS := -Wno-unused-result
CFLAGS := $(CC_WARNINGS) -std=c90 -O3 -lpthread -lm
TARGET = main

all: $(TARGET)

%: %.c lab1_IO.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rf $(TARGET)

.PHONY: all clean
