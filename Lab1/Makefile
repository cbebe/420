DATA := data_input data_output
UTIL := matrixgen serialtester
util: $(UTIL)

CFLAGS := -Wall -Wpedantic

%: %.c
	gcc $^ $(CFLAGS) -o $@ 

SERIAL_OBJS := lab1_IO.o serialtester.o
serialtester: $(SERIAL_OBJS)
	gcc $^ $(CFLAGS) -o $@

%.o: %.c %.h
	gcc -o $@ -c $< $(CFLAGS)

clean:
	rm -f $(UTIL) $(SERIAL_OBJS) $(DATA)

.PHONY: util clean