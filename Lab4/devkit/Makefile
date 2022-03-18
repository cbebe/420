CFLAGS := -O3

datatrim: datatrim.c
	gcc $(CFLAGS) $^ -o $@

serialtester: serialtester.c ../src/Lab4_IO.c
	gcc $(CFLAGS) $^ -o $@ -lm

clean:
	rm -f datatrim serialtester

.PHONY: clean