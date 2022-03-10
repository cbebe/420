CC ?= gcc
# Don't bug us about C90!!
CFLAGS := -Wall -O3


test%: test.c ../src/Lab3IO.c scheme%.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

# Don't use parallel team inside gaussian and jordan
test00: test00.c ../src/Lab3IO.c scheme00.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

# Protect test.c from being deleted
# Don't name any other source file as test* or it will be nuked!
clean:
	@cp test.c src_test.c
	@cp test00.c src_test00.c
	rm -f test*
	@mv src_test.c test.c
	@mv src_test00.c test00.c
