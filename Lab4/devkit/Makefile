CFLAGS := -O3

serialtester: serialtester.c ../src/Lab4_IO.c
	gcc $(CFLAGS) $^ -o $@ -lm

%: %.c
	gcc $(CFLAGS) $^ -o $@

clean:
	rm -f datatrim serialtester average

.PHONY: clean