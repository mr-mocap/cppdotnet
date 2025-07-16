INCLUDE_DIRS = ./include

LIB_BASENAME = cppdotnet
LIB_NAME = lib$(LIB_BASENAME).a
BUILD_DIR = build
LIB_PATH = $(BUILD_DIR)/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTRA_LIBS = -luuid

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I . $(INC_PARAMS) $(DEBUG_FLAGS)
CXXFLAGS_PCM=-std=c++20 -fmodules-ts -x c++-header -I . $(INC_PARAMS)
CXXFLAGS_MODULE = -std=c++20 -fmodules-ts -c

LIB_SRC  = $(wildcard *.cpp \
                      src/System/*.cpp \
                      src/System/Collections/Generic/*.cpp \
					  src/System/Diagnostics/*.cpp \
					  src/System/Diagnostics/Metrics/*.cpp \
					  src/System/Diagnostics/Private/*.cpp \
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

SYSTEM_MODULE_ENUMS = System/Base.hpp \
					  System/Base64FormattingOptions.hpp \
					  System/ConsoleColor.hpp \
					  System/ConsoleKey.hpp \
					  System/ConsoleModifiers.hpp \
					  System/DateTimeKind.hpp \
					  System/DayOfWeek.hpp \
					  System/EnvironmentVariableTarget.hpp \
					  System/PlatformID.hpp \
					  System/TypeCode.hpp
SYSTEM_MODULE_HEADERS = $(wildcard System/Private/*.hpp System/*.hpp)
SYSTEM_MODDULE_SRC = $(wildcard src/System/*.cpp)
#SYSTEM_MODULE_PCMS = $(patsubst %.hpp,%.pcm,${SYSTEM_MODULE_ENUMS}) $(patsubst %.hpp,%.pcm,${SYSTEM_MODULE_HEADERS})
SYSTEM_MODULE_PCMS = $(patsubst %.hpp,%.pcm,${SYSTEM_MODULE_HEADERS})

MODULES = System

src/System/System.ixx: $(MODULE_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE) $< -o $@.o

# Create Header Units
%.pcm : %.hpp
	mkdir -p ${dir $@}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PCM) $< -o $(basename $@.pcm)

System: $(SYSTEM_MODULE_PCMS)

build/%.o : %.cpp
	mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS) $(MODULES)
	
all: $(LIB_OBJS)
	ar -crs $(LIB_PATH) $(LIB_OBJS)
	ranlib $(LIB_PATH)

lib: all

modules: $(MODULES)

.PHONY: clean
clean:
	rm -rf build

-include $(LIB_DEP)
