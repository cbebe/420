EXE := matrixgen serialtester lab1
DATA := data_input data_output

SIZE ?= 10
BOUND ?= 5

test: data_input serialtester
	@./lab1
	@tail -n1 data_output
	@./serialtester

mat: matrixgen
	@./matrixgen -s $(SIZE) -b $(BOUND)

data_input: matrixgen
	@./matrixgen -s 1000 -b 1000000

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

.PHONY: exe clean deploy test mat
