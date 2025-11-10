BUILD_DIR = build
LIB_BASENAME = cppdotnet
LIB_NAME = lib$(LIB_BASENAME).a
LIB_PATH = $(BUILD_DIR)

INCLUDE_DIR = ./include
SRC_DIR = ./src/$(LIB_BASENAME)
INC_PARAMS = $(INCLUDE_DIR:%=-I%) -I.
DEBUG_FLAGS = -g3

EXTRA_LIBS = -luuid

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP $(INC_PARAMS) $(DEBUG_FLAGS) $(EXTRA_LIBS)

TARGET = $(BUILD_DIR)/$(LIB_NAME)

LIB_SRC  = $(wildcard *.cpp \
                      $(SRC_DIR)/System/*.cpp \
                      $(SRC_DIR)/System/Collections/Generic/*.cpp \
                      $(SRC_DIR)/System/Collections/Specialized/*.cpp \
					  $(SRC_DIR)/System/Diagnostics/*.cpp \
					  $(SRC_DIR)/System/Diagnostics/Private/*.cpp \
					  $(SRC_DIR)/System/Diagnostics/Metrics/*.cpp \
					  $(SRC_DIR)/System/IO/*.cpp \
					  $(SRC_DIR)/System/Text/*.cpp \
					  $(SRC_DIR)/System/Xml/*.cpp)
LIB_OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,${LIB_SRC})
LIB_DEP  = $(BUILD_DIR)/*.d \
           $(BUILD_DIR)/System/*.d \
		   $(BUILD_DIR)/System/Collections/Generic/*.d \
		   $(BUILD_DIR)/System/Diagnostics/*.d \
		   $(BUILD_DIR)/System/Diagnostics/Metrics/*.d \
		   $(BUILD_DIR)/System/Diagnostics/Private/*.d \
		   $(BUILD_DIR)/System/IO/*.d \
		   $(BUILD_DIR)/System/Text/*.d \
		   $(BUILD_DIR)/System/Xml/*.d

.PHONY: all
all: lib
#	@ar -crs $(TARGET) $(LIB_OBJS)
#	@ranlib $(TARGET)

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

.PHONY: lib
lib: $(TARGET) | $(BUILD_DIR)

$(BUILD_DIR)/libSystem.Base.a:
	$(MAKE) -f Makefile.System.Base

$(BUILD_DIR)/libSystem.Collections.a:
	$(MAKE) -f Makefile.System.Collections

$(BUILD_DIR)/libSystem.IO.a:
	$(MAKE) -f Makefile.System.IO

$(BUILD_DIR)/libSystem.Diagnostics.a:
	$(MAKE) -f Makefile.System.Diagnostics

$(BUILD_DIR)/libSystem.Xml.a:
	$(MAKE) -f Makefile.System.Xml

#$(TARGET): $(LIB_OBJS)
#	@ar -crs $(TARGET) $(LIB_OBJS)
#	@ranlib $(TARGET)

$(TARGET): $(BUILD_DIR)/libSystem.Diagnostics.a $(BUILD_DIR)/libSystem.Xml.a $(BUILD_DIR)/libSystem.IO.a $(BUILD_DIR)/libSystem.Collections.a $(BUILD_DIR)/libSystem.Base.a
#	@ar -crs $(TARGET) $^
#	@ranlib $(TARGET)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.cpp
	@mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)
	
default: lib

.PHONY: clean
clean:
	@rm -rf build

-include $(LIB_DEP)
