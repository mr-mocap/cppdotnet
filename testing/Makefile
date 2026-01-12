INCLUDE_DIRS = ../libs/include

BINARY_NAME = code_tests
LIB_BUILD_DIR = ../libs/build
LIB_BASE_NAME = cppdotnet
LIB_NAME = $(LIB_BASE_NAME).a
LIB_TARGET = $(LIB_BUILD_DIR)/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTERNAL_LIBS = -lSystem.Diagnostics -lSystem.Xml -lSystem.IO -lSystem.Collections -lSystem.Base -luuid
CXXFLAGS=-std=c++20 -W -Wall -Wextra -MMD -MP -pedantic -I . $(INC_PARAMS) $(DEBUG_FLAGS)
LDFLAGS=-L$(LIB_BUILD_DIR)

TESTS = Activity ActivitySource BinaryWriter BitConverter Console ConsoleTraceListener Convert \
	Counter DateOnly DateTime DateTimeOffset Debug DefaultTraceListener Delegates \
	Dictionary Enum Environment Exception Guid ICollection IDictionary IList Int32 \
	LinkedList List Nullable Path Progress ReadOnlySpan Span Stack Stopwatch StringBuilder \
	StringReader StringWriter TimeOnly TimeSpan Trace TraceSource ValueTuple Version \
	NameTable XmlAttribute XmlDeclaration XmlDocument XmlElement XmlDocumentType XmlProcessingInstruction \
	XmlText XmlNodeWriteTo XmlTextWriter
TEST_BINARIES = $(patsubst %,Test%,${TESTS})
PASSING_TESTS = $(patsubst %,%.pass,${TEST_BINARIES})

default: all

$(LIB_BUILD_DIR):
	@$(MAKE) --directory=../libs lib

$(LIB_TARGET): $(LIB_BUILD_DIR)
	@$(MAKE) --directory=../libs lib

.PHONY: lib
lib: $(LIB_TARGET)
	@$(MAKE) --directory=../libs lib

.PHONY: all
all: $(LIB_TARGET) $(PASSING_TESTS)

.PHONY: clean
clean:
	@rm -f ./*.o
	@rm -f ./*.d
	@rm -f $(TEST_BINARIES)
	@rm -f $(PASSING_TESTS)

.PHONY: cleanlib
cleanlib:
	@$(MAKE) --directory=.. --quiet cleanlib

$(TEST_BINARIES): %: %.cpp
	@echo -n $@ [BUILDING] ...
	@$(CXX) -o $@ $< $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(EXTERNAL_LIBS)

$(PASSING_TESTS): %.pass: %
	@./$< >/dev/null 2>/dev/null
	@echo [PASSED]
	@touch $@

-include *.d
