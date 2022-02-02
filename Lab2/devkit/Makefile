# Not our problem :^)
NO_WARN :=
CFLAGS := -O3 -Wall $(NO_WARN)
LDFLAGS := -lm -lpthread
BIN := client attacker arrayRW

all: $(BIN)

%: %.c common.h
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(BIN)

.PHONY: all clean
