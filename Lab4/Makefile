EXE := main datatrim serialtester

run: main serialtester
	./main
	./serialtester

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

%: src/%.c src/page_rank.c
	cd src && $(MAKE) $@ && cp $@ ..

submit: submit.sh
	./$<

report: lab_report.pdf

%.pdf: %.md
	pandoc $< -o $@

clean:
	rm -f $(EXE)
	cd devkit && $(MAKE) $@
	cd src && $(MAKE) $@

.PHONY: run clean submit report