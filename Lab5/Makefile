DIR := Lab5
NUM_TASKS := 1 2 3 4
TASKS := $(NUM_TASKS:%=src/task%.txt)

submit: $(TASKS) submit.sh
	./submit.sh

datatrim: devkit/datatrim.c
	cd devkit && $(MAKE) $@ && cp $@ ..

pull:
	rsync -av cloud:$(DIR)/ .

push:
	rsync -av . cloud:$(DIR)

push_d:
	ssh cloud 'rm -rf $(DIR)'

clean:
	cd devkit && $(MAKE) clean
	rm -f datatrim

src/%.txt: shell/%.scala src
	cp $< $@

src:
	mkdir -p $@

.PHONY: pull push push_d clean submit
