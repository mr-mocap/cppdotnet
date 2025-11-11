BUILD_DIR = build
LIB_BASENAME = System.IO
LIB_NAME = lib$(LIB_BASENAME).a
LIB_PATH = $(BUILD_DIR)

INCLUDE_DIR = ./include
SRC_DIR = ./src/cppdotnet
INC_PARAMS = $(INCLUDE_DIR:%=-I%) -I.
DEBUG_FLAGS = -g3

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP $(INC_PARAMS) $(DEBUG_FLAGS)

TARGET = $(BUILD_DIR)/$(LIB_NAME)

LIB_SRC  = $(SRC_DIR)/System/Console.cpp \
           $(SRC_DIR)/System/IO/BinaryWriter.cpp \
           $(SRC_DIR)/System/IO/ConsoleStream.cpp \
           $(SRC_DIR)/System/IO/FileStream.cpp \
           $(SRC_DIR)/System/IO/Exception.cpp \
           $(SRC_DIR)/System/IO/MemoryStream.cpp \
           $(SRC_DIR)/System/IO/NullStream.cpp \
           $(SRC_DIR)/System/IO/Path.cpp \
           $(SRC_DIR)/System/IO/Stream.cpp \
           $(SRC_DIR)/System/IO/StreamReader.cpp \
           $(SRC_DIR)/System/IO/StreamWriter.cpp \
           $(SRC_DIR)/System/IO/StringReader.cpp \
           $(SRC_DIR)/System/IO/StringWriter.cpp \
           $(SRC_DIR)/System/IO/TextReader.cpp \
           $(SRC_DIR)/System/IO/TextWriter.cpp

LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,${LIB_SRC})

LIB_DEP  = $(patsubst $(BUILD_DIR)/%.o,$(BUILD_DIR)/%.d,${LIB_OBJS})

.PHONY: all
all: lib
	@ar -crs $(TARGET) --record-libdeps "-lSystem.Collections -lSystem.Base" $(LIB_OBJS)
	@ranlib $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

.PHONY: lib
lib: $(TARGET) | $(BUILD_DIR)

$(TARGET): $(LIB_OBJS)
	@ar -crs $(TARGET) $(LIB_OBJS)
	@ranlib $(TARGET)

.PHONY: $(LIB_BASENAME)
$(LIB_BASENAME): $(LIB_OBJS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)

default: lib

-include $(LIB_DEP)