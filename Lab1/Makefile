CC ?= gcc
CC_WARNINGS := -w
CFLAGS := $(CC_WARNINGS) -std=c90 -O3 -lpthread -lm
TARGET = main

all: $(TARGET)

$(TARGET): $(TARGET).c lab1_IO.c
	$(CC) $^ $(CFLAGS) -o $@

clean:
	rm -rf $(TARGET)
