CFLAGS := -Wall -Wpedantic -O3

%: %.c ../src/Lab3IO.c
	$(CC) $(CFLAGS) $^ -o $@ -lm

speedup: speedup.c
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f datagen serialtester speedup
