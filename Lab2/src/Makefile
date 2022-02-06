# Submission Makefile
CFLAGS := -Wall -Wpedantic -O3

BINS := main1 main2 main3 main4
DEPOBJS := server.o operate.o common.o read_write_lock.o

all: $(BINS)

main%: scheme%.o $(DEPOBJS)
	$(CC) $^ $(CFLAGS) -o $@ -lpthread

%.o: %.c
	$(CC) -c $< $(CFLAGS) -o $@

clean:
	rm -f $(BINS) $(DEPOBJS)

.PHONY: all clean
