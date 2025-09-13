INCLUDE_DIRS := include
SRC_DIR := src
BUILD_DIR := module_build

INC_PARAMS  := -I. $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS := -g3

HEADER_UNIT_CACHE_DIR := gcm.cache
CXX_STANDARD := -std=c++20

-include Makefile.defs

-include Makefile.rules

default: all

all: normalized_dependencies.generated
	@echo DONE

print:
	@echo SYSTEM_HEADER_UNIT_GCMS: $(SYSTEM_HEADER_UNIT_GCMS)

#$(BUILD_DIR)/System.o: $(SRC_DIR)/System/System.ixx
System.o: System/System.ixx
	@echo Module 'System' Built
#	@$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -fmodules-ts -c -x c++ $< -o $@

list_dependencies: list_dependencies.cpp
	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -o $@ $<

list_modules: list_modules.cpp
	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -o $@ $<

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(HEADER_UNIT_CACHE_DIR)
	@rm -f system_header_units.generated dependencies.generated normalized_dependencies.generated

-include $(BUILD_DIR)/System/*.normalized.d