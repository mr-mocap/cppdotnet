INCLUDE_DIRS = ./include

LIB_BASENAME = cppdotnet
LIB_NAME = lib$(LIB_BASENAME).a
LIB_PATH = build/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

MODULE_FLAGS=-fmodules-ts

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I . $(INC_PARAMS) $(DEBUG_FLAGS) $(MODULE_FLAGS)

LIB_SRC  = $(wildcard *.cpp src/System/*.cpp src/System/Collections/Generic/*.cpp src/System/Diagnostics/*.cpp src/System/Diagnostics/Private/*.cpp src/System/IO/*.cpp src/System/Numerics/*.cpp src/System/Text/Json/*.cpp)
LIB_OBJS = $(patsubst %.cpp,build/%.o,${LIB_SRC})
LIB_DEP  = $(LIB_PATH)/*.d $(LIB_PATH)/src/System/*.d $(LIB_PATH)/src/System/Collections/Generic/*.d $(LIB_PATH)/src/System/Diagnostics/*.d $(LIB_PATH)/src/System/Diagnostics/Private/*.d $(LIB_PATH)/src/System/IO/*.d $(LIB_PATH)/src/System/Numerics/*.d $(LIB_PATH)/src/System/Text/Json/*.d

build/%.o : %.cpp
	echo Making build directory...
	mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)
	
all: $(LIB_OBJS)
	ar -crs $(LIB_PATH) $(LIB_OBJS)
	ranlib $(LIB_PATH)

lib: all

.PHONY: clean
clean:
	rm -rf build

-include $(LIB_DEP)
