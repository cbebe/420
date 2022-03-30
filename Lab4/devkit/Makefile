CFLAGS := -O3
LDFLAGS := -lm

%: %.c ../src/Lab4_IO.c
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f datatrim serialtester average serial

.PHONY: clean