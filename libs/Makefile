INCLUDE_DIRS = ./include

LIB_BASENAME = cppdotnet
LIB_NAME = lib$(LIB_BASENAME).a
LIB_PATH = build/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTRA_LIBS = -luuid

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I . $(INC_PARAMS) $(DEBUG_FLAGS) $(EXTRA_LIBS)

LIB_SRC  = $(wildcard *.cpp \
                      src/System/*.cpp \
                      src/System/Collections/Generic/*.cpp \
                      src/System/Collections/Specialized/*.cpp \
					  src/System/Diagnostics/*.cpp \
					  src/System/Diagnostics/Private/*.cpp \
					  src/System/Diagnostics/Metrics/*.cpp \
					  src/System/IO/*.cpp \
					  src/System/Text/*.cpp)
LIB_OBJS = $(patsubst %.cpp,build/%.o,${LIB_SRC})
LIB_DEP  = $(LIB_PATH)/*.d \
           $(LIB_PATH)/src/System/*.d \
		   $(LIB_PATH)/src/System/Collections/Generic/*.d \
		   $(LIB_PATH)/src/System/Diagnostics/*.d \
		   $(LIB_PATH)/src/System/Diagnostics/Metrics/*.d \
		   $(LIB_PATH)/src/System/Diagnostics/Private/*.d \
		   $(LIB_PATH)/src/System/IO/*.d \
		   $(LIB_PATH)/src/System/Text/*.d

build/%.o : %.cpp
	@mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)
	
all: $(LIB_OBJS)
	@ar -crs $(LIB_PATH) $(LIB_OBJS)
	@ranlib $(LIB_PATH)

lib: all

.PHONY: clean
clean:
	@rm -rf build

-include $(LIB_DEP)
