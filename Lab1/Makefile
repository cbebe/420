EXE := matrixgen serialtester lab1
DATA := data_input data_output

test: $(DATA) serialtester
	@./serialtester

data_input: matrixgen
	@./matrixgen -s 100 -b 1000000

data_output: lab1
	@./lab1

exe: $(EXE)

CFLAGS := -Wall -Wpedantic

%: %.c lab1_IO.c
	gcc $^ $(CFLAGS) -o $@ 

clean:
	rm -f $(EXE) $(DATA)

deploy: clean
	rsync -av . cloud:Lab1

.PHONY: exe clean deploy test