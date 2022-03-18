EXE := main datatrim serialtester

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

%: src/%.c
	cd src && $(MAKE) $@ && cp $@ ..

clean:
	rm -f $(EXE)
	cd devkit && $(MAKE) $@
	cd src && $(MAKE) $@

.PHONY: clean