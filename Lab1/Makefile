DATA := data_input data_output
EXE := matrixgen serialtester lab1
exec: $(EXE)

CFLAGS := -Wall -Wpedantic

%: %.c lab1_IO.c
	gcc $^ $(CFLAGS) -o $@ 

clean:
	rm -f $(EXE) $(DATA)

.PHONY: exe clean