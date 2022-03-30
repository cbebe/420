EXE := main datatrim serialtester average serial
REPORT := lab_report.pdf

run: main serialtester datatrim average test.sh
	./test.sh

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

%: src/%.c src/page_rank.c
	cd src && $(MAKE) $@ && cp $@ ..

submit: submit.sh
	./$<

report: $(REPORT)

%.pdf: %.md
	pandoc $< -o $@

clean:
	rm -f $(EXE) $(REPORT) *.zip
	cd devkit && $(MAKE) $@
	cd src && $(MAKE) $@

deploy: clean
	rsync -av . cloud:Lab4

clean_data: clean
	rm -f results*.txt data_input* data_output average*.txt baseline*.txt

.PHONY: run clean submit report