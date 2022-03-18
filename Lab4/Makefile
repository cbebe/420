DEVKIT := datatrim serialtester

%: devkit/%.c
	cd devkit && $(MAKE) $@ && cp $@ ..

clean:
	rm -f $(DEVKIT)
	cd devkit && $(MAKE) $@

.PHONY: clean