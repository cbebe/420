DATA := data_input data_output
UTIL := matrixgen serialtester
util: $(UTIL)

CFLAGS := -Wall -Wpedantic

%: %.c lab1_IO.c
	gcc $^ $(CFLAGS) -o $@ 

clean:
	rm -f $(UTIL) $(DATA)

.PHONY: util clean