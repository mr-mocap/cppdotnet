INCLUDE_DIRS = ../libs/include

BINARY_NAME = code_tests
LIB_BUILD_DIR = ../libs/build
LIB_BASE_NAME = cppdotnet
LIB_NAME = $(LIB_BASE_NAME).a
LIB_PATH = $(LIB_BUILD_DIR)/lib$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3
OBJS = TestDefaultTraceListener.o \
	TestConsoleTraceListener.o \
	TestConsole.o \
	TestDebug.o \
	TestException.o \
	TestEnvironment.o \
	TestVersion.o \
	TestStringReader.o \
	TestStringWriter.o \
	TestEnum.o \
	TestBitConverter.o \
	TestConvert.o \
	TestSpan.o \
	TestReadOnlySpan.o \
	TestStringBuilder.o \
	TestInt32.o \
	TestNullable.o \
	TestDelegates.o \
	TestLinkedList.o \
	TestList.o \
	TestTimeSpan.o \
	TestDateTime.o \
	TestICollection.o \
	TestDictionary.o \
	TestTimeOnly.o \
	TestDateTimeOffset.o \
	TestDateOnly.o \
	TestStack.o \
	TestPath.o \
	TestValueTuple.o \
	main.o

CXXFLAGS=-std=c++20 -W -Wall -Wextra -MMD -MP -pedantic -I . $(INC_PARAMS) $(DEBUG_FLAGS)
LDFLAGS=-L$(LIB_BUILD_DIR)

#%.o: %.cpp
	#$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)

default: test

$(LIB_BUILD_DIR):
	cd .. && $(MAKE) lib

$(LIB_PATH): $(LIB_BUILD_DIR)
	cd .. && $(MAKE) lib

.PHONY: lib
lib: $(LIB_PATH)
	cd .. && $(MAKE) lib

$(BINARY_NAME): $(LIB_PATH) $(OBJS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) $(OBJS) -o $(BINARY_NAME) $(LDFLAGS) -L ../libs/build -l $(LIB_BASE_NAME)

.PHONY: test
test: $(LIB_PATH) $(BINARY_NAME)

run_test: test
	./$(BINARY_NAME)

.PHONY: clean
clean:
	rm -f ./*.o
	rm -f ./$(BINARY_NAME)

.PHONY: cleanlib
cleanlib:
	cd .. && make cleanlib

-include *.d