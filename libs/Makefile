INCLUDE_DIRS := include
SRC_DIRS := src
MODULE_BUILD_DIR := module_build

INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTRA_LIBS = -luuid

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I. $(INC_PARAMS) $(DEBUG_FLAGS)
CXXFLAGS_MODULE_HEADER_DEPENDENCY  = -std=c++20 -fmodules-ts -fmodule-header -x c++-user-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_HEADER_UNIT        = -std=c++20 -fmodules-ts -fmodule-header -x c++-user-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT = -std=c++20 -fmodules-ts -fmodule-header=system -x c++-system-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_IMP = -std=c++20 -fmodules-ts -I. $(INC_PARAMS)
CXXFLAGS_MODULE = -std=c++20 -fmodules-ts -I. -c -x c++ $(INC_PARAMS)

HEADER_UNIT_CACHE = gcm.cache

# Find all imports of compiler system std headers...
# NOTE: For now, let's just limit it to the root System module headers.
SYSTEM_HEADER_UNITS := $(shell grep -Po "(?<=^import <)[a-z]+(?=>;\$$)" include/System/*.hpp | cut -d: -f2 | sort --unique)
SYSTEM_HEADER_FILE_DIR := $(shell g++ -v -x c++ -E /dev/null 2>/dev/stdout 1>/dev/null | awk '/#include <...> search starts here:/ {flag=1; next} /End of search list./ {flag=0} flag' | cut -f 2 -d" " | head -n1)
SYSTEM_HEADER_UNIT_GCMS := $(SYSTEM_HEADER_UNITS:%=$(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm)

SYSTEM_MODULE_HEADER_UNITS_GENERATED   = $(MODULE_BUILD_DIR)/generated.system_module_header_units
SYSTEM_MODULE_SOURCE_DEPENDENCIES_GENERATED = $(MODULE_BUILD_DIR)/generated.system_module_src_dependencies

SYSTEM_MODULE_HEADERS := $(wildcard $(INCLUDE_DIRS)/System/*.hpp $(INCLUDE_DIRS)/System/Private/*.hpp $(INCLUDE_DIRS)/System/Numerics/*.hpp)
SYSTEM_MODULE_SOURCES := $(wildcard $(INCLUDE_DIRS)/System/*.cpp)

LIB_HDRS := $(shell find $(INCLUDE_DIRS) -name "*.hpp")
LIB_SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")

SYSTEM_MODULE_HEADER_DEPS := $(SYSTEM_MODULE_HEADERS:%.hpp=$(MODULE_BUILD_DIR)/%.d)
SYSTEM_MODULE_SOURCE_DEPS := $(SYSTEM_MODULE_SOURCES:%.cpp=$(MODULE_BUILD_DIR)/%.d)

SYSTEM_MODULE_HEADER_UNITS := $(SYSTEM_MODULE_HEADERS:%.hpp=$(HEADER_UNIT_CACHE)/%.hpp.gcm)


all: system_header_units system_module_dependencies system_module_header_units
	@echo DONE

.PHONY: print
print:
	@echo "Here are all the system headers imported by the base System module:"
	@echo $(shell list_system_includes "include/System/*.hpp")

.PHONY: system_header_units
system_header_units: $(SYSTEM_HEADER_UNIT_GCMS)
	@echo System Header Units Generated!

.PHONY: system_module_dependencies
#system_module_dependencies: system_module_header_dependencies
system_module_dependencies: system_module_header_dependencies system_module_source_dependencies
	@echo System Module Dependencies Created

.PHONY: system_module_header_dependencies
system_module_header_dependencies: $(MODULE_BUILD_DIR) $(SYSTEM_MODULE_HEADER_DEPS)
	@echo System Module Header Dependencies Generated

.PHONY: system_module_source_dependencies
system_module_source_dependencies: $(SYSTEM_MODULE_SOURCE_DEPENDENCIES_GENERATED)
	@echo System Module Source Dependencies Generated

.PHONY: system_module_header_units
system_module_header_units: $(MODULE_BUILD_DIR) $(SYSTEM_MODULE_HEADER_UNITS)
	@echo System Module Header Units Created

$(SYSTEM_MODULE_SOURCE_DEPENDENCIES_GENERATED): $(MODULE_BUILD_DIR) $(SYSTEM_MODULE_SOURCE_DEPS)
	@touch $@

$(MODULE_BUILD_DIR):
	@echo Making Build Directory
	@mkdir -p $@


.PHONY: clean
clean: remove_module_build_dir remove_header_unit_cache

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
	$(shell ./generate_user_header_dependency_file $< "include/" >$@; sed --in-place 's/.hpp/.hpp.gcm/g' $@; echo "\n" >>$@)
	$(shell ./generate_user_header_dependency_file $< "include/" >>$@; echo "" >>$@)

# System Module Source Dependencies Rule
$(MODULE_BUILD_DIR)/%.d : %.cpp
	@mkdir -p ${dir $@}
	@touch $@
# 	Generate the .d file
	$(CXX) -I. $(INC_PARAMS) -MM -MF $@ -MT $@ $<
#   Concatenate all continuation lines in the .d file
# 	NOTE: Don't forget that a literal $ has to be expressed as $$
	@sed -e ':a' -e '/\\$$/N' -e 's/\\\n//g' -e 'ta' --in-place $@

# System Module Header Unit Generation Rule
$(HEADER_UNIT_CACHE)/%.hpp.gcm: %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) $<

# Compiler Header Unit Generation Rule
$(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)%.gcm: $(SYSTEM_HEADER_FILE_DIR)/%
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT) $(patsubst $(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm,%,$@)

-include $(SYSTEM_MODULE_HEADER_DEPS)