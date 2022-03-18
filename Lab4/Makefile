EXE := main datatrim serialtester

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

%: src/%.c
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

.PHONY: clean submit report