datatrim: datatrim.c
	gcc $^ -o $@

serialtester: serialtester.c ../src/Lab4_IO.c
	gcc $^ -o $@ -lm

clean:
	rm -f datatrim serialtester

.PHONY: clean