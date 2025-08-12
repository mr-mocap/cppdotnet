INCLUDE_DIRS := ./include
SRC_DIRS := src
MODULE_BUILD_DIR := module_build

LIB_BASENAME = cppdotnet
LIB_NAME = lib$(LIB_BASENAME).a
BUILD_DIR = build
LIB_PATH = $(BUILD_DIR)/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTRA_LIBS = -luuid

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I. $(INC_PARAMS) $(DEBUG_FLAGS)
#CXXFLAGS_PCM=-std=c++20 -fmodules-ts -x c++-header -MMD -MP -I . $(INC_PARAMS)
CXXFLAGS_MODULE_HEADER_UNIT = -std=c++20 -fmodules-ts -fmodule-header -x c++-user-header -I. $(INC_PARAMS)
CXXFLAGS_MODULE_IMP = -std=c++20 -fmodules-ts -I. $(INC_PARAMS)
CXXFLAGS_MODULE = -std=c++20 -fmodules-ts -I. -x c++ $(INC_PARAMS)

LIB_SRC  = $(wildcard *.cpp \
                      ${SRC_DIRS}/System/*.cpp \
                      ${SRC_DIRS}/System/Collections/Generic/*.cpp \
                      ${SRC_DIRS}/System/Collections/Specialized/*.cpp \
					  ${SRC_DIRS}/System/Diagnostics/*.cpp \
					  ${SRC_DIRS}/System/Diagnostics/Metrics/*.cpp \
					  ${SRC_DIRS}/System/Diagnostics/Private/*.cpp \
					  ${SRC_DIRS}/System/IO/*.cpp \
					  ${SRC_DIRS}/System/Text/*.cpp)
LIB_OBJS = $(patsubst %.cpp,build/%.o,${LIB_SRC})
LIB_DEP  = $(BUILD_DIR)/*.d \
           $(BUILD_DIR)/src/System/*.d \
		   $(BUILD_DIR)/src/System/Collections/Generic/*.d \
		   $(BUILD_DIR)/src/System/Diagnostics/*.d \
		   $(BUILD_DIR)/src/System/Diagnostics/Metrics/*.d \
		   $(BUILD_DIR)/src/System/Diagnostics/Private/*.d \
		   $(BUILD_DIR)/src/System/IO/*.d \
		   $(BUILD_DIR)/src/System/Text/*.d

HEADER_UNIT_CACHE = gcm.cache/,
SYSTEM_MODULE_ENUMS = include/System/Private/enum.hpp \
					  include/System/Base.hpp \
					  include/System/Base64FormattingOptions.hpp \
					  include/System/ConsoleColor.hpp \
					  include/System/ConsoleKey.hpp \
					  include/System/ConsoleModifiers.hpp \
					  include/System/DateTimeKind.hpp \
					  include/System/DayOfWeek.hpp \
					  include/System/EnvironmentVariableTarget.hpp \
					  include/System/PlatformID.hpp \
					  include/System/TypeCode.hpp

SYSTEM_MODULE_DELEGATES = include/System/Private/Delegate.hpp \
						  include/System/Action.hpp \
						  include/System/Comparison.hpp \
						  include/System/Converter.hpp \
						  include/System/EventHandler.hpp \
						  include/System/Func.hpp \
						  include/System/Predicate.hpp

SYSTEM_MODULE_HEADER_ONLY_FILES = $(SYSTEM_MODULE_ENUMS) $(SYSTEM_MODULE_DELEGATES)
SYSTEM_MODULE_OTHER_HEADER_FILES = include/System/BitConverter.hpp \
								include/System/Boolean.hpp \
								include/System/Byte.hpp \
								include/System/Concepts.hpp \
								include/System/Console.hpp \
								include/System/ConsoleKeyInfo.hpp \
								include/System/Convert.hpp \
								include/System/DateOnly.hpp \
								include/System/DateTime.hpp \
								include/System/DateTimeOffset.hpp \
								include/System/Enum.hpp \
								include/System/Environment.hpp \
								include/System/EventArgs.hpp \
								include/System/Exception.hpp \
								include/System/Guid.hpp \
								include/System/Int16.hpp \
								include/System/Int32.hpp \
								include/System/Int64.hpp \
								include/System/IObservable.hpp \
								include/System/IObserver.hpp \
								include/System/Math.hpp \
								include/System/Nullable.hpp \
								include/System/OperatingSystem.hpp \
								include/System/ReadOnlySpan.hpp \
								include/System/Span.hpp \
								include/System/TimeOnly.hpp \
								include/System/TimeSpan.hpp \
								include/System/ValueTuple.hpp \
								include/System/Version.hpp
SYSTEM_MODULE_HEADER_ONLY_GCMS = $(patsubst %.hpp,%.hpp.gcm,$(SYSTEM_MODULE_HEADER_ONLY_FILES))
SYSTEM_MODULE_OTHER_HEADER_GCMS = $(patsubst %.hpp,%.hpp.gcm,$(SYSTEM_MODULE_OTHER_HEADER_FILES))
SYSTEM_MODULE_HEADERS = $(SYSTEM_MODULE_ENUMS) $(SYSTEM_MODULE_DELEGATES) $(SYSTEM_MODULE_OTHER_HEADER_FILES)

SYSTEM_MODULE_SRCS := $(shell find $(SRC_DIRS) -name "*.cpp")
SYSTEM_MODULE_DEPS = $(patsubst %.cpp,$(MODULE_BUILD_DIR)/%.d,${SYSTEM_MODULE_SRCS})
SYSTEM_MODULE_DEPENDENCIES_MADE = $(MODULE_BUILD_DIR)/generated.dot_d
#SYSTEM_MODULE_OBJS := $(patsubst %.cpp,$(MODULE_BUILD_DIR)/%.o,${SYSTEM_MODULE_SRCS})
SYSTEM_MODULE_OBJS := $(patsubst %.cpp,$(MODULE_BUILD_DIR)/%.o,src/System/Exception.cpp)

HEADER_UNITS_GENERATED = $(MODULE_BUILD_DIR)/generated.header_units
HEADER_ONLY_UNITS_GENERATED = $(MODULE_BUILD_DIR)/generated.header_only_units
OTHER_HEADER_UNITS_GENERATED = $(MODULE_BUILD_DIR)/generated.other_header_units

# For some reason, I have to process all of the enum headers BEFORE they are used in other classes
#SYSTEM_MODULE_PCMS = $(patsubst %.hpp,${HEADER_UNIT_CACHE}/%.hpp.gcm,${SYSTEM_MODULE_HEADERS})

IO_HEADER_ONLY_FILES = include/System/IO/FileAccess.hpp \
                       include/System/IO/FileMode.hpp \
		       include/System/IO/MatchCasing.hpp \
		       include/System/IO/MatchType.hpp \
		       include/System/IO/SeekOrigin.hpp \
		       include/System/IO/UnixFileMode.hpp
IO_OTHER_HEADER_FILES = include/System/IO/BinaryWriter.hpp \
			include/System/IO/ConsoleStream.hpp \
			include/System/IO/FileStream.hpp \
			include/System/IO/FileStreamOptions.hpp \
			include/System/IO/IOException.hpp \
			include/System/IO/MemoryStream.hpp \
			include/System/IO/NullStream.hpp \
			include/System/IO/Path.hpp \
			include/System/IO/Stream.hpp \
			include/System/IO/StreamReader.hpp \
			include/System/IO/StreamWriter.hpp \
			include/System/IO/StringReader.hpp \
			include/System/IO/StringWriter.hpp \
			include/System/IO/TextReader.hpp \
			include/System/IO/StringWriter.hpp
IO_HEADER_ONLY_GCMS = $(patsubst %.hpp,%.hpp.gcm,$(IO_HEADER_ONLY_FILES))
IO_OTHER_HEADER_GCMS = $(patsubst %.hpp,%.hpp.gcm,$(IO_OTHER_HEADER_FILES))
IO_SRC = $(wildcard src/System/*.cpp)
IO_OBJS = $(patsubst %.cpp,${MODULE_BUILD_DIR}/%.o,${IO_SRC})

DIAGNOSTICS_HEADER_ONLY_FILES = include/System/Diagnostics/ActivitySamplingResult.hpp \
                                include/System/Diagnostics/SampleActivity.hpp \
                                include/System/Diagnostics/SourceLevels.hpp \
                                include/System/Diagnostics/TraceEventType.hpp \
                                include/System/Diagnostics/TraceLevel.hpp \
                                include/System/Diagnostics/TraceOptions.hpp \
								include/System/Diagnostics/Private/Formatting.hpp
DIAGNOSTICS_OTHER_HEADER_FILES = include/System/Diagnostics/Activity.hpp \
                                 include/System/Diagnostics/ActivityListener.hpp \
								 include/System/Diagnostics/ActivitySource.hpp \
								 include/System/Diagnostics/ActivitySpanId.hpp \
								 include/System/Diagnostics/ActivityTraceId.hpp \
								 include/System/Diagnostics/Switch.hpp \
								 include/System/Diagnostics/BooleanSwitch.hpp \
								 include/System/Diagnostics/TextWriterTraceListener.hpp \
								 include/System/Diagnostics/ConsoleTraceListener.hpp \
								 include/System/Diagnostics/Debug.hpp \
								 include/System/Diagnostics/Debugger.hpp \
								 include/System/Diagnostics/TraceFilter.hpp \
								 include/System/Diagnostics/TraceEventCache.hpp \
								 include/System/Diagnostics/TraceListener.hpp \
								 include/System/Diagnostics/DefaultTraceListener.hpp \
								 include/System/Diagnostics/DiagnosticSource.hpp \
								 include/System/Diagnostics/DiagnosticListener.hpp \
								 include/System/Diagnostics/TraceEventCache.hpp \
								 include/System/Diagnostics/EventTypeFilter.hpp \
								 include/System/Diagnostics/SourceFilter.hpp \
								 include/System/Diagnostics/SourceSwitch.hpp \
								 include/System/Diagnostics/Stopwatch.hpp \
								 include/System/Diagnostics/TraceListenerCollection.hpp \
								 include/System/Diagnostics/Trace.hpp \
								 include/System/Diagnostics/TraceSource.hpp \
								 include/System/Diagnostics/TraceSwitch.hpp \
								 include/System/Diagnostics/Private/DebugAndTraceCommon.hpp

DIAGNOSTICS_HEADER_ONLY_GCMS = $(patsubst %.hpp,%.hpp.gcm,$(DIAGNOSTICS_HEADER_ONLY_FILES))
DIAGNOSTICS_OTHER_HEADER_GCMS = $(patsubst %.hpp,%.hpp.gcm,$(DIAGNOSTICS_OTHER_HEADER_FILES))

#src/System/%.cpp : src/System/%.o
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_IMP) -fmodule-file=$< -c $< -o $(basename $@.o)
#	echo "-fmodule-file=$< -c $< -o $(basename $@.o)"

# Rule to create Header Units
# ${MODULE_BUILD_DIR}/%.pcm : %.hpp
# 	@mkdir -p ${dir $@}
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PCM) $< -o $(basename $@.pcm)

$(MODULE_BUILD_DIR)/%.d : %.cpp
	@mkdir -p ${dir $@}
	@touch $@
# 	Generate the .d file
	$(CXX) -I. $(INC_PARAMS) -MM -MF $@ -MT $(patsubst %.d,%.o,$@) $<
#   Concatenate all continuation lines in the .d file
# 	NOTE: Don't forget that a literal $ has to be expressed as $$
	@sed -e ':a' -e '/\\$$/N' -e 's/\\\n//g' -e 'ta' --in-place $@

# Module implementation files
$(MODULE_BUILD_DIR)/%.o : %.cpp
	@mkdir -p ${dir $@}
	$(CXX) $(CXXFLAGS_MODULE_IMP) $< -c -o $@

# Rule to create Header Units
%.hpp.gcm : %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) $<

$(OTHER_HEADER_UNITS_GENERATED): $(SYSTEM_MODULE_OTHER_HEADER_GCMS) $(IO_OTHER_HEADER_GCMS) $(DIAGNOSTICS_OTHER_HEADER_FILES)
	@touch $(OTHER_HEADER_UNITS_GENERATED)
	@echo Other Header Units DONE!

$(HEADER_ONLY_UNITS_GENERATED): $(SYSTEM_MODULE_HEADER_ONLY_GCMS) $(IO_HEADER_ONLY_GCMS) $(DIAGNOSTICS_HEADER_ONLY_GCMS)
	@touch $(HEADER_ONLY_UNITS_GENERATED)
	@echo Header-Only Header Units DONE!

$(HEADER_UNITS_GENERATED): $(HEADER_ONLY_UNITS_GENERATED) $(OTHER_HEADER_UNITS_GENERATED)
	@touch $(HEADER_UNITS_GENERATED)
	@echo Header Units Generated

# Generate .d dependency files for the Makefile to include in later compilations
$(SYSTEM_MODULE_DEPENDENCIES_MADE): $(SYSTEM_MODULE_DEPS)
	@touch $(SYSTEM_MODULE_DEPENDENCIES_MADE)
	@echo Compilation Dependencies Generated

#src/System/System.ixx: GenerateHeaderUnits $(SYSTEM_MODULE_OBJS)
src/System/System.ixx: $(SYSTEM_MODULE_DEPENDENCIES_MADE) $(HEADER_UNITS_GENERATED) $(SYSTEM_MODULE_OBJS)
	$(CXX) $(CXXFLAGS_MODULE) -c $@ -o System.o

build/%.o : %.cpp
	@mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)
	
# Clean only the .d dependency files
.PHONY: clean-module-deps
clean-module-deps:
	@find $(MODULE_BUILD_DIR) -name "*.d" -delete
	@rm $(SYSTEM_MODULE_DEPENDENCIES_MADE)

.PHONY: clean-module-objs
clean-module-objs:
	find $(MODULE_BUILD_DIR) -name "*.o" -delete

all: $(LIB_OBJS)
	@echo Creating static library
	@ar -crs $(LIB_PATH) $(LIB_OBJS)
	@ranlib $(LIB_PATH)

lib: all

#modules: GenerateHeaderUnits src/System/System.ixx
#modules: generate-module-deps src/System/System.ixx
modules: src/System/System.ixx

.PHONY: clean
clean:
	@rm -rf $(MODULE_BUILD_DIR)
	@rm -rf gcm.cache

-include $(SYSTEM_MODULE_DEPS)
