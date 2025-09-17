INCLUDE_DIRS := include
SRC_DIR := src
BUILD_DIR := module_build

LIB_NAME := cppdotnet
TARGET := lib$(LIB_NAME).a

EXTRA_LIBS := -luuid

INC_PARAMS  := -I. $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS := -g3

HEADER_UNIT_CACHE_DIR := gcm.cache
CXX_STANDARD := -std=c++20

-include Makefile.defs

default: all

.PHONY: all
all: lib

.PHONY: lib
lib: generate_prerequisites $(BUILD_DIR)/$(TARGET)
	@echo DONE

print:
	@echo $(SYSTEM_MODULE_PARTITION_OBJS_BUILT)

$(BUILD_DIR)/$(TARGET): $(SYSTEM_MODULE).c++m | $(BUILD_DIR)
	@$(AR) -crs $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(SYSTEM_MODULE_INTERFACE_OBJ) $(SYSTEM_MODULE_PARTITION_OBJS_BUILT)
	@ranlib $(BUILD_DIR)/$(TARGET)
	@echo Library \'$(LIB_NAME)\' Built

# .PHONY: $(SYSTEM_MODULE).c++m
# $(SYSTEM_MODULE).c++m: $(BUILD_DIR)/$(SYSTEM_MODULE_INTERFACE_OBJ)
# 	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -fmodules-ts -c -x c++ $< -o $(BUILD_DIR)/$@

# $(HEADER_UNIT_CACHE_DIR)/$(SYSTEM_MODULE).gcm: build_system_module_partitions build_system_module | $(SYSTEM_MODULE).o

.PHONY: build_system_module
build_system_module : $(SYSTEM_MODULE_INTERFACE_OBJ) build_system_module_partitions
	@echo Interface Module \'System\' Built

.PHONY: build_system_module_partitions
build_system_module_partitions : $(SYSTEM_MODULE_PARTITION_OBJS)

$(SYSTEM_MODULE_INTERFACE_OBJ): $(SYSTEM_MODULE_INTERFACE_SRC) $(SYSTEM_MODULE_PARTITION_OBJS)
	@echo Building Interface Module '$(SYSTEM_MODULE)'
	$(CXX) $(CPPFLAGS) $(CXX_STANDARD) $(INC_PARAMS) -fmodules-ts -c -x c++ $(SRC_DIR)/$(SYSTEM_MODULE_INTERFACE_SRC) -o $@

.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR)
	@rm -rf $(HEADER_UNIT_CACHE_DIR)

-include Makefile.rules
-include $(BUILD_DIR)/Makefile.compiler_header_unit_targets
-include $(BUILD_DIR)/Makefile.module.system.deps
-include $(BUILD_DIR)/System/*.normalized.d