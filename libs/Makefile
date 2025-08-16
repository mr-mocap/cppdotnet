INCLUDE_DIRS := include
SRC_DIRS := src
MODULE_BUILD_DIR := module_build

INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

UUID_LIB = uuid
UUID_LIB_HEADERS = uuid/uuid.h
UUID_LIB_HEADER_FILE_DIR = /usr/include
UUID_LIB_LINK = -l$(UUID_LIB)

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I. $(INC_PARAMS) $(DEBUG_FLAGS)
CXXFLAGS_MODULE_HEADER_DEPENDENCY  = -std=c++20 -fmodules-ts -x c++-user-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_HEADER_UNIT        = -std=c++20 -fmodule-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT = -std=c++20 -fmodules-ts -x c++-system-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_IMP = -std=c++20 -fmodules-ts -I. $(INC_PARAMS)
#CXXFLAGS_MODULE = -std=c++20 -fmodules-ts -I. -c -x c++ $(INC_PARAMS)

HEADER_UNIT_CACHE = gcm.cache

#SYSTEM_MODULE_HEADERS = $(wildcard $(INCLUDE_DIRS)/System/*.hpp $(INCLUDE_DIRS)/System/Private/*.hpp $(INCLUDE_DIRS)/System/Numerics/*.hpp)
SYSTEM_MODULE_HEADERS = $(wildcard $(INCLUDE_DIRS)/System/*.hpp $(INCLUDE_DIRS)/System/Private/*.hpp $(INCLUDE_DIRS)/System/Numerics/*.hpp $(INCLUDE_DIRS)/System/IO/*.hpp)
SYSTEM_MODULE_SOURCES = $(wildcard $(INCLUDE_DIRS)/System/*.cpp)

# Find all imports of compiler system std headers...
# NOTE: For now, let's just limit it to the root System module headers.
SYSTEM_HEADER_UNITS = $(shell ./list_system_includes "include/System/*.hpp include/System/Private/*.hpp include/System/Numerics/*.hpp")
SYSTEM_HEADER_FILE_DIR = $(shell g++ -v -x c++ -E /dev/null 2>/dev/stdout 1>/dev/null | awk '/#include <...> search starts here:/ {flag=1; next} /End of search list./ {flag=0} flag' | cut -f 2 -d" " | head -n1)
SYSTEM_HEADER_UNIT_GCMS = $(SYSTEM_HEADER_UNITS:%=$(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm)

UUID_LIB_HEADER_UNITS = $(UUID_LIB_HEADERS)
UUID_LIB_HEADER_UNIT_GCMS = $(UUID_LIB_HEADER_UNITS:%=$(HEADER_UNIT_CACHE)$(UUID_LIB_HEADER_FILE_DIR)/%.gcm)

LIB_HDRS = $(shell find $(INCLUDE_DIRS) -name "*.hpp")
LIB_SRCS = $(shell find $(SRC_DIRS) -name "*.cpp")

SYSTEM_MODULE_HEADER_DEPS = $(SYSTEM_MODULE_HEADERS:%.hpp=$(MODULE_BUILD_DIR)/%.d)
SYSTEM_MODULE_SOURCE_DEPS = $(SYSTEM_MODULE_SOURCES:%.cpp=$(MODULE_BUILD_DIR)/%.d)

SYSTEM_MODULE_HEADER_UNIT_GCMS = $(SYSTEM_MODULE_HEADERS:%.hpp=$(HEADER_UNIT_CACHE)/%.hpp.gcm)
SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE = sys_module_header_unit_build_order.generated

all: system_header_units system_module_dependencies system_module_header_unit_build_order system_module_header_units
	@echo DONE

.PHONY: print
print:
	@echo $(SYSTEM_HEADER_UNITS)

generate_build_order: generate_build_order.cpp
	@echo Making generate_build_order
	$(CXX) -std=c++20 -o $@ $<

.PHONY: system_header_units
system_header_units: $(SYSTEM_HEADER_UNIT_GCMS) $(UUID_LIB_HEADER_UNIT_GCMS)
	@echo System Header Units Generated!

.PHONY: system_module_dependencies
system_module_dependencies: system_module_header_dependencies system_module_source_dependencies
	@echo System Module Dependencies Created

.PHONY: system_module_header_dependencies
system_module_header_dependencies: $(MODULE_BUILD_DIR) $(SYSTEM_MODULE_HEADER_DEPS)
	@echo System Module Header Dependencies Generated

.PHONY: system_module_source_dependencies
system_module_source_dependencies: $(MODULE_BUILD_DIR) $(SYSTEM_MODULE_SOURCE_DEPS)
	@echo System Module Source Dependencies Generated

.PHONY: system_module_header_unit_build_order
system_module_header_unit_build_order: $(SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE)
	@echo System Module Header Unit build order generated

$(SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE): generate_build_order
	@echo $(SYSTEM_MODULE_HEADERS) | ./generate_build_order >$(SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE)
# 	Build all the System module's header units
	@while read line; do \
		$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) "$$line"; \
	done < $(SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE)
		

.PHONY: system_module_header_units
system_module_header_units: $(MODULE_BUILD_DIR) $(SYSTEM_MODULE_HEADER_UNIT_GCMS)
	@echo System Module Header Units Created

$(MODULE_BUILD_DIR):
	@echo Making Build Directory
	@mkdir -p $@


.PHONY: clean
clean: remove_module_build_dir remove_header_unit_cache
	rm -f $(SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE)

.PHONY: remove_module_build_dir
remove_module_build_dir:
	@rm -rf $(MODULE_BUILD_DIR)

.PHONY: remove_header_unit_cache
remove_header_unit_cache:
	@rm -rf $(HEADER_UNIT_CACHE)

#
# RULES
#

# System Module Header Dependencies Rule
$(MODULE_BUILD_DIR)/%.d : %.hpp
	@mkdir -p ${dir $@}
# 	Generate the .d file
	$(shell ./generate_user_header_dependency_file $< "$(INCLUDE_DIRS)/" >$@; sed --in-place 's/.hpp/.hpp.gcm/g' $@; echo "\n" >>$@)
	$(shell ./generate_user_header_dependency_file $< "$(INCLUDE_DIRS)/" >>$@; echo "" >>$@)

# System Module Source Dependencies Rule
$(MODULE_BUILD_DIR)/%.d : %.cpp
	@mkdir -p ${dir $@}
# 	Generate the .d file
# 	$(shell ./generate_user_header_dependency_file $< "$(INCLUDE_DIRS)/" >$@; sed --in-place 's/.hpp/.hpp.gcm/g' $@; echo "\n" >>$@)
# 	$(shell ./generate_user_header_dependency_file $< "$(SRC_DIRS)/" >>$@; echo "" >>$@)

# System Module Header Unit Generation Rule
$(HEADER_UNIT_CACHE)/%.hpp.gcm: %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) $<

# Compiler Header Unit Generation Rule
$(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)%.gcm: $(SYSTEM_HEADER_FILE_DIR)/%
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT) $(patsubst $(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm,%,$@)

# Other Header Unit Generation Rule
$(HEADER_UNIT_CACHE)$(UUID_LIB_HEADER_FILE_DIR)/%.gcm: $(UUID_LIB_HEADER_FILE_DIR)/%
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT) $(patsubst $(HEADER_UNIT_CACHE)$(UUID_LIB_HEADER_FILE_DIR)/%.gcm,%,$@)

# Module implementation files
$(MODULE_BUILD_DIR)/%.o : %.cpp
	@mkdir -p ${dir $@}
	$(CXX) $(CXXFLAGS_MODULE_IMP) $< -c -o $@

#-include $(SYSTEM_MODULE_HEADER_DEPS)