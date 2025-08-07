default: all

all: run_test

lib:
	cd libs && $(MAKE) lib

.PHONY: test
test:
	cd testing && $(MAKE) test

.PHONY: clean
cleanlib:
	cd libs && $(MAKE) clean

.PHONY: cleantest
cleantest:
	cd testing && $(MAKE) clean

.PHONY: run_test
run_test: test
	@cd testing && $(MAKE) run_test

.PHONY: modules
modules: 
	@cd libs && $(MAKE) modules
