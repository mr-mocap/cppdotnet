default: all

all: test

lib:
	$(MAKE) --directory=libs lib

.PHONY: test
test:
	@$(MAKE) --directory=testing

.PHONY: clean
cleanlib:
	@$(MAKE) --directory=libs --quiet clean

.PHONY: cleantest
cleantest:
	@$(MAKE) --directory=testing --quiet clean
