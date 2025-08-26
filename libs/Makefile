INCLUDE_DIRS := include
SRC_DIRS := src
MODULE_BUILD_DIR := module_build

INC_PARAMS = -I. $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

UUID_LIB = uuid
UUID_LIB_HEADERS = uuid/uuid.h
UUID_LIB_HEADER_FILE_DIR = /usr/include
UUID_LIB_LINK = -l$(UUID_LIB)

CXX_STANDARD=c++20
CXXFLAGS=-std=$(CXX_STANDARD) -W -Wall -pedantic -MMD -MP $(INC_PARAMS) $(DEBUG_FLAGS)
CXXFLAGS_MODULE_HEADER_DEPENDENCY  = -std=$(CXX_STANDARD) -fmodules-ts -x c++-user-header $(INC_PARAMS)
#CXXFLAGS_MODULE_HEADER_UNIT        = -std=$(CXX_STANDARD) -fmodule-header $(INC_PARAMS)
CXXFLAGS_MODULE_HEADER_UNIT        = -std=$(CXX_STANDARD) -fmodule-header $(INC_PARAMS)
#CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT = -std=$(CXX_STANDARD) -fmodules-ts -x c++-system-header $(INC_PARAMS)
CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT = -std=$(CXX_STANDARD) -fmodules-ts -fmodule-header=system -x c++-system-header $(INC_PARAMS)
CXXFLAGS_MODULE_IMP = -std=$(CXX_STANDARD) -fmodules-ts $(INC_PARAMS)
CXXFLAGS_MODULE = -std=$(CXX_STANDARD) -fmodules-ts -c -x c++ $(INC_PARAMS)

HEADER_UNIT_CACHE = gcm.cache

LIB_HDRS = $(shell find $(INCLUDE_DIRS) -name "*.hpp")
LIB_SRCS = $(shell find $(SRC_DIRS) -name "*.cpp")

COMPILER_DEFAULT_SEARCH_DIRS = $(shell g++ -v -x c++ -E /dev/null 2>/dev/stdout 1>/dev/null | awk '/#include <...> search starts here:/ {flag=1; next} /End of search list./ {flag=0} flag')

#SYSTEM_MODULE_HEADERS = $(wildcard $(INCLUDE_DIRS)/System/*.hpp $(INCLUDE_DIRS)/System/Private/*.hpp $(INCLUDE_DIRS)/System/Numerics/*.hpp)
SYSTEM_MODULE_HEADERS = $(wildcard $(INCLUDE_DIRS)/System/*.hpp $(INCLUDE_DIRS)/System/Private/*.hpp $(INCLUDE_DIRS)/System/Numerics/*.hpp $(INCLUDE_DIRS)/System/IO/*.hpp $(INCLUDE_DIRS)/System/Text/*.hpp $(INCLUDE_DIRS)/System/Collections/Generic/*.hpp $(INCLUDE_DIRS)/System/Collections/Generic/Private/*.hpp $(INCLUDE_DIRS)/System/Collections/Specialized/*.hpp)
SYSTEM_MODULE_SOURCES = $(wildcard $(INCLUDE_DIRS)/System/*.cpp)

# Find all imports of compiler system std headers...
# NOTE: For now, let's just limit it to the root System module headers.
SYSTEM_HEADER_UNITS = $(shell ./list_system_includes "include/System/*.hpp include/System/Private/*.hpp include/System/Numerics/*.hpp")

# NOTE: The following variable is to get around g++ crashes when generating header units.
#       This process of compiling them is order-dependent, so I created this variable so
#       that the exact order could be tweaked.
#       It is derived from the output of "./list_system_includes "$(LIB_HDRS)".
SYSTEM_HEADER_UNITS_BUILD_ORDER = algorithm any array bit cassert cctype charconv chrono cmath compare concepts cstddef cstdint cstring ios filesystem exception system_error format functional initializer_list iosfwd iterator limits list map memory mutex numbers optional ranges set source_location span stack stdexcept string string_view utility tuple type_traits unordered_map unordered_set variant vector 
SYSTEM_HEADER_FILE_DIR = $(shell echo "$(COMPILER_DEFAULT_SEARCH_DIRS)" | cut -f 2 -d" " | head -n1)
SYSTEM_HEADER_UNIT_GCMS = $(SYSTEM_HEADER_UNITS_BUILD_ORDER:%=$(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm)

UUID_LIB_HEADER_UNITS = $(UUID_LIB_HEADERS)
UUID_LIB_HEADER_UNIT_GCMS = $(UUID_LIB_HEADER_UNITS:%=$(HEADER_UNIT_CACHE)$(UUID_LIB_HEADER_FILE_DIR)/%.gcm)

SYSTEM_MODULE_HEADER_DEPS = $(SYSTEM_MODULE_HEADERS:%.hpp=$(MODULE_BUILD_DIR)/%.d)
SYSTEM_MODULE_SOURCE_DEPS = $(SYSTEM_MODULE_SOURCES:%.cpp=$(MODULE_BUILD_DIR)/%.d)

SYSTEM_MODULE_HEADER_UNIT_GCMS = $(SYSTEM_MODULE_HEADERS:%.hpp=$(HEADER_UNIT_CACHE)/%.hpp.gcm)
SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE = sys_module_header_unit_build_order.generated

#all: system_header_units system_module_dependencies system_module_header_unit_build_order system_module_header_units
all: system_header_units $(MODULE_BUILD_DIR)/System.o
	@echo DONE

.PHONY: print
print:
	@echo $(SYSTEM_HEADER_UNITS)

generate_build_order: generate_build_order.cpp
	@echo Making generate_build_order
	$(CXX) -std=$(CXX_STANDARD) -o $@ $<

list_dependencies: list_dependencies.cpp
	@echo Making 'list_dependencies'
	$(CXX) -std=$(CXX_STANDARD) -o $@ $<

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
	@echo Generating System Module Header Units Build Order
	@echo $(SYSTEM_MODULE_HEADERS) | ./generate_build_order >$(SYSTEM_MODULE_HEADER_UNITS_BUILD_ORDER_FILE)
# 	Build all the System module's header units
	@while read line; do \
		$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) "$$line" || break; \
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

# System MODULES
$(MODULE_BUILD_DIR)/System.o: src/System/System.ixx \
                              $(MODULE_BUILD_DIR)/System/EventArgs.o \
                              $(MODULE_BUILD_DIR)/System/IComparable.o \
							  $(MODULE_BUILD_DIR)/System/Private_Delegate.o \
							  $(MODULE_BUILD_DIR)/System/Action.o \
							  $(MODULE_BUILD_DIR)/System/Predicate.o \
							  $(MODULE_BUILD_DIR)/System/Exception.o \
							  $(MODULE_BUILD_DIR)/System/Private_enum.o \
							  $(MODULE_BUILD_DIR)/System/ValueTuple.o \
							  $(MODULE_BUILD_DIR)/System/Nullable.o \
							  $(MODULE_BUILD_DIR)/System/IObserver.o \
							  $(MODULE_BUILD_DIR)/System/IObservable.o \
							  $(MODULE_BUILD_DIR)/System/Comparison.o \
							  $(MODULE_BUILD_DIR)/System/Base.o \
							  $(MODULE_BUILD_DIR)/System/Base64FormattingOptions.o \
							  $(MODULE_BUILD_DIR)/System/ConsoleColor.o \
							  $(MODULE_BUILD_DIR)/System/ConsoleKey.o \
							  $(MODULE_BUILD_DIR)/System/ConsoleModifiers.o \
							  $(MODULE_BUILD_DIR)/System/TypeCode.o \
							  $(MODULE_BUILD_DIR)/System/ConsoleKeyInfo.o \
							  $(MODULE_BUILD_DIR)/System/DateTimeKind.o \
							  $(MODULE_BUILD_DIR)/System/DayOfWeek.o \
							  $(MODULE_BUILD_DIR)/System/PlatformID.o \
							  $(MODULE_BUILD_DIR)/System/Func.o \
							  $(MODULE_BUILD_DIR)/System/TimeSpan.o \
							  $(MODULE_BUILD_DIR)/System/DateOnly.o \
							  $(MODULE_BUILD_DIR)/System/TimeOnly.o \
							  $(MODULE_BUILD_DIR)/System/Converter.o \
							  $(MODULE_BUILD_DIR)/System/EventHandler.o \
							  $(MODULE_BUILD_DIR)/System/BitConverter.o \
							  $(MODULE_BUILD_DIR)/System/DateTime.o \
							  $(MODULE_BUILD_DIR)/System/IDisposable.o \
							  $(MODULE_BUILD_DIR)/System/IConvertible.o \
							  $(MODULE_BUILD_DIR)/System/DateTimeOffset.o \
							  $(MODULE_BUILD_DIR)/System/DateOnly_imp.o \
							  $(MODULE_BUILD_DIR)/System/TimeOnly_imp.o \
							  $(MODULE_BUILD_DIR)/System/TimeSpan_impl.o \
							  $(MODULE_BUILD_DIR)/System/DateTime_impl.o \
							  $(MODULE_BUILD_DIR)/System/Enum.o \
							  $(MODULE_BUILD_DIR)/System/Span.o \
							  $(MODULE_BUILD_DIR)/System/ReadOnlySpan.o \
							  $(MODULE_BUILD_DIR)/System/Guid.o \
							  $(MODULE_BUILD_DIR)/System/Version.o \
							  $(MODULE_BUILD_DIR)/System/OperatingSystem.o

# 							  $(MODULE_BUILD_DIR)/System/Environment.o

#
# RULES
#

# Modules
$(MODULE_BUILD_DIR)/%.o: src/%.ixx
	@mkdir -p ${dir $@}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE) -o $@ $<

# System Module Header Dependencies Rule
# $(MODULE_BUILD_DIR)/%.d : %.hpp
# 	@mkdir -p ${dir $@}
# # 	Generate the .d file
# 	@./generate_user_header_dependency_file $< "$(INCLUDE_DIRS)/" >$@; sed --in-place 's/.hpp/.hpp.gcm/g' $@; echo "\n" >>$@
# 	@./generate_user_header_dependency_file $< "$(INCLUDE_DIRS)/" >>$@; echo "" >>$@

# System Module Source Dependencies Rule
# $(MODULE_BUILD_DIR)/%.d : %.cpp
# 	@mkdir -p ${dir $@}
# 	Generate the .d file

# System Module Header Unit Generation Rule
# $(HEADER_UNIT_CACHE)/%.hpp.gcm: %.hpp
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) $<

# Compiler Header Unit Generation Rule
$(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm: $(SYSTEM_HEADER_FILE_DIR)/%
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT) $(patsubst $(HEADER_UNIT_CACHE)$(SYSTEM_HEADER_FILE_DIR)/%.gcm,%,$@)

# Other Header Unit Generation Rule
$(HEADER_UNIT_CACHE)$(UUID_LIB_HEADER_FILE_DIR)/%.gcm: $(UUID_LIB_HEADER_FILE_DIR)/%
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_SYSTEM_HEADER_UNIT) $(patsubst $(HEADER_UNIT_CACHE)$(UUID_LIB_HEADER_FILE_DIR)/%.gcm,%,$@)

# Module implementation files
# $(MODULE_BUILD_DIR)/%.o : %.cpp
# 	@mkdir -p ${dir $@}
# 	$(CXX) $(CXXFLAGS_MODULE_IMP) $< -c -o $@

# -include $(SYSTEM_MODULE_HEADER_DEPS)
#-include modules.d