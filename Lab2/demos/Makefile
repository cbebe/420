# Not our problem :^)
NO_WARN := -Wno-unused-result -Wno-pointer-to-int-cast
CFLAGS := -O3 -Wall $(NO_WARN)
LDFLAGS := -lpthread
BIN := client server

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(BIN)

.PHONY: all clean