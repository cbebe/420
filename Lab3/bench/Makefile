CC ?= gcc
# Don't bug us about C90!!
CFLAGS := -Wall -O3

test%: test.c ../src/Lab3IO.c scheme%.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

# Protect test.c from being deleted
# Don't name any other source file as test* or it will be nuked!
clean:
	@cp test.c src_test.c
	rm -f test*
	@mv src_test.c test.c
