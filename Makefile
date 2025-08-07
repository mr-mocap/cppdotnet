default: all

all: test

lib:
	@cd libs && $(MAKE) lib

.PHONY: test
test:
	@cd testing && $(MAKE)

.PHONY: clean
cleanlib:
	@cd libs && $(MAKE) clean

.PHONY: cleantest
cleantest:
	@cd testing && $(MAKE) clean
