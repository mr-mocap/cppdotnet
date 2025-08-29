INCLUDE_DIRS := include
SRC_DIR := src
BUILD_DIR := module_build

INC_PARAMS  := -I. $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS := -g3

HEADER_UNIT_CACHE_DIR := gcm.cache
CXX_STANDARD := -std=c++20

-include Makefile.defs

-include Makefile.rules


all: system_header_units.generated normalized_dependencies.generated
	@echo DONE

print:
	@echo $(SUFFIXES)

normalized_dependencies.generated: dependencies.generated $(BUILT_NORMALIZED_DEPS)
	@touch $@
	@echo System Module Normalized Dependencies Generated!

dependencies.generated: $(BUILT_DEPS)
	@touch $@
	@echo System Module Dependencies Generated!

system_header_units.generated: $(SYSTEM_HEADER_UNIT_GCMS)
	@touch $@
	@echo System Header Units Generated!

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(HEADER_UNIT_CACHE_DIR)
	@rm -f system_header_units.generated dependencies.generated normalized_dependencies.generated
