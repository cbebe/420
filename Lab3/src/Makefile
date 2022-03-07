CC ?= gcc
# Don't bug us about C90!!
CFLAGS := -Wall -O3

all: main

run: main
	./main

# Uses the best scheme, we haven't decided yet which one that is
main: main.c Lab3IO.c schemess.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

main%: main.c Lab3IO.c scheme%.c
	$(CC) $(CFLAGS) -fopenmp -o $@ $^

# Protect main.c from being deleted
# Don't name any other source file as main* or it will be nuked!
clean:
	@cp main.c src.c
	rm -f main*
	@mv src.c main.c
