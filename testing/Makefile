INCLUDE_DIRS = ../libs/include

BINARY_NAME = code_tests
LIB_BUILD_DIR = ../libs/build
LIB_BASE_NAME = cppdotnet
LIB_NAME = $(LIB_BASE_NAME).a
LIB_PATH = $(LIB_BUILD_DIR)/lib$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTERNAL_LIBS = -l$(LIB_BASE_NAME) -luuid
CXXFLAGS=-std=c++20 -W -Wall -Wextra -MMD -MP -pedantic -I . $(INC_PARAMS) $(DEBUG_FLAGS)
LDFLAGS=-L$(LIB_BUILD_DIR)

TESTS = Activity BinaryWriter BitConverter Console ConsoleTraceListener Convert \
		Counter DateOnly DateTime DateTimeOffset Debug DefaultTraceListener Delegates \
		Dictionary Enum Environment Exception Guid ICollection IDictionary IList Int32 \
		LinkedList List Nullable Path ReadOnlySpan Span Stack Stopwatch StringBuilder \
		StringReader StringWriter TimeOnly TimeSpan Trace ValueTuple Version
TEST_BINARIES = $(patsubst %,Test%,${TESTS})
PASSING_TESTS = $(patsubst %,%.pass,${TEST_BINARIES})

%: %.cpp
	@echo -n $@ [BUILDING] ...
	@$(CXX) -o $@ $< $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(EXTERNAL_LIBS)

%.pass: %
	@./$< >/dev/null 2>/dev/null
	@echo [PASSED]
	@touch $@

default: all

$(LIB_BUILD_DIR):
	@cd .. && $(MAKE) lib

$(LIB_PATH): $(LIB_BUILD_DIR)
	@cd .. && $(MAKE) lib

.PHONY: lib
lib: $(LIB_PATH)
	@cd .. && $(MAKE) lib

TestVersion: TestVersion.cpp

TestVersion.pass: TestVersion

TestValueTuple: TestValueTuple.cpp

TestValueTuple.pass: TestValueTuple

TestTrace: TestTrace.cpp

TestTrace.pass: TestTrace

TestTimeSpan: TestTimeSpan.cpp

TestTimeSpan.pass: TestTimeSpan

TestTimeOnly: TestTimeOnly.cpp

TestTimeOnly.pass: TestTimeOnly

TestStringWriter: TestStringWriter.cpp

TestStringWriter.pass: TestStringWriter

TestStringReader: TestStringReader.cpp

TestStringReader.pass: TestStringReader

TestStringBuilder: TestStringBuilder.cpp

TestStringBuilder.pass: TestStringBuilder

TestStopwatch: TestStopwatch.cpp

TestStopwatch.pass: TestStopwatch

TestStack: TestStack.cpp

TestStack.pass: TestStack

TestSpan: TestSpan.cpp

TestSpan.pass: TestSpan

TestReadOnlySpan: TestReadOnlySpan.cpp

TestReadOnlySpan.pass: TestReadOnlySpan

TestPath: TestPath.cpp

TestPath.pass: TestPath

TestNullable: TestNullable.cpp

TestNullable.pass: TestNullable

TestMeter: TestMeter.cpp

TestMeter.pass: TestMeter

TestList: TestList.cpp

TestList.pass: TestList

TestLinkedList: TestLinkedList.cpp

TestLinkedList.pass: TestLinkedList

TestInt32: TestInt32.cpp

TestInt32.pass: TestInt32

TestIList: TestIList.cpp

TestIList.pass: TestIList

TestIDictionary: TestIDictionary.cpp

TestIDictionary.pass: TestIDictionary

TestICollection: TestICollection.cpp

TestICollection.pass: TestICollection

TestGuid: TestGuid.cpp

TestGuid.pass: TestGuid

TestException: TestException.cpp

TestException.pass: TestException

TestEnvironment: TestEnvironment.cpp

TestEnvironment.pass: TestEnvironment

TestEnum: TestEnum.cpp

TestEnum.pass: TestEnum

TestDictionary: TestDictionary.cpp

TestDictionary.pass: TestDictionary

TestDelegates: TestDelegates.cpp

TestDelegates.pass: TestDelegates

TestDefaultTraceListener: TestDefaultTraceListener.cpp

TestDefaultTraceListener.pass: TestDefaultTraceListener

TestDebug: TestDebug.cpp

TestDebug.pass: TestDebug

TestDateTimeOffset: TestDateTimeOffset.cpp

TestDateTimeOffset.pass: TestDateTimeOffset

TestDateTime: TestDateTime.cpp

TestDateTime.pass: TestDateTime

TestDateOnly: TestDateOnly.cpp

TestDateOnly.pass: TestDateOnly

TestCounter: TestCounter.cpp

TestCounter.pass: TestCounter

TestConvert: TestConvert.cpp

TestConvert.pass: TestConvert

TestConsoleTraceListener: TestConsoleTraceListener.cpp

TestConsoleTraceListener.pass: TestConsoleTraceListener

TestConsole: TestConsole.cpp

TestConsole.pass: TestConsole

TestBitConverter: TestBitConverter.cpp

TestBitConverter.pass: TestBitConverter

TestBinaryWriter: TestBinaryWriter.cpp

TestBinaryWriter.pass: TestBinaryWriter

TestActivity: TestActivity.cpp

TestActivity.pass: TestActivity

all: $(PASSING_TESTS) $(LIB_PATH)

.PHONY: clean
clean:
	@rm -f ./*.o
	@rm -f ./*.d
	@rm -f $(TEST_BINARIES)
	@rm -f $(PASSING_TESTS)

.PHONY: cleanlib
cleanlib:
	@cd .. && make cleanlib

-include *.d
