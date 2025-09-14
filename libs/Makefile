INCLUDE_DIRS := include
SRC_DIR := src
BUILD_DIR := module_build

INC_PARAMS  := -I. $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS := -g3

HEADER_UNIT_CACHE_DIR := gcm.cache
CXX_STANDARD := -std=c++20

-include Makefile.defs

default: all

all: normalized_dependencies.generated build_system_module
	@echo DONE

print:
	@echo SYSTEM_HEADER_UNIT_GCMS: $(SYSTEM_HEADER_UNIT_GCMS)

.PHONY: build_system_module
build_system_module : System.o build_system_module_partitions
	@echo Interface Module \'System\' Built

.PHONY: build_system_module_partitions
build_system_module_partitions : $(SYSTEM_MODULE_OBJS)

$(SYSTEM_MODULE_INTERFACE_OBJ): $(SYSTEM_MODULE_INTERFACE_SRC) $(SYSTEM_MODULE_PARTITION_OBJS)
	@echo Building Interface Module '$(SYSTEM_MODULE)'
	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -fmodules-ts -c -x c++ $(SRC_DIR)/$(SYSTEM_MODULE_INTERFACE_SRC) -o $(BUILD_DIR)/$@

list_dependencies: list_dependencies.cpp
	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -o $@ $<

list_modules: list_modules.cpp
	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -o $@ $<

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(HEADER_UNIT_CACHE_DIR)
	@rm -f system_header_units.generated dependencies.generated normalized_dependencies.generated

-include Makefile.rules

-include $(BUILD_DIR)/System/*.normalized.d