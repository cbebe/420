# Not our problem :^)
NO_WARN :=
CFLAGS := -O3 -Wall $(NO_WARN)
LDFLAGS := -lm
BIN := client attacker

all: $(BIN)

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)

clean:
	rm -f $(BIN)

.PHONY: all clean