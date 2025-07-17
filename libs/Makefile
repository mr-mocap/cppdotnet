INCLUDE_DIRS = ./include

LIB_BASENAME = cppdotnet
LIB_NAME = lib$(LIB_BASENAME).a
BUILD_DIR = build
LIB_PATH = $(BUILD_DIR)/$(LIB_NAME)
INC_PARAMS = $(INCLUDE_DIRS:%=-I%)
DEBUG_FLAGS = -g3

EXTRA_LIBS = -luuid

CXXFLAGS=-std=c++20 -W -Wall -pedantic -MMD -MP -I . $(INC_PARAMS) $(DEBUG_FLAGS)
CXXFLAGS_PCM=-std=c++20 -fmodules-ts -x c++-header -MMD -MP -I . $(INC_PARAMS)
CXXFLAGS_MODULE_HEADER_UNIT = -std=c++20 -fmodules-ts
CXXFLAGS_MODULE_IMP = -std=c++20 -fmodules-ts

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

SYSTEM_MODULE_ENUMS = include/System/Base.hpp \
					  include/System/Base64FormattingOptions.hpp \
					  include/System/ConsoleColor.hpp \
					  include/System/ConsoleKey.hpp \
					  include/System/ConsoleModifiers.hpp \
					  include/System/DateTimeKind.hpp \
					  include/System/DayOfWeek.hpp \
					  include/System/EnvironmentVariableTarget.hpp \
					  include/System/PlatformID.hpp \
					  include/System/TypeCode.hpp
SYSTEM_MODULE_HEADERS = $(wildcard include/System/Private/*.hpp include/System/*.hpp)
SYSTEM_MODDULE_SRC = $(wildcard src/System/*.cpp)
SYSTEM_MODULE_OBJS = $(patsubst %.cpp,module_build/%.o,${SYSTEM_MODULE_SRC})

# For some reason, I have to process all of the enum headers BEFORE they are used in other classes
SYSTEM_MODULE_PCMS = $(patsubst %.hpp,%.pcm,${SYSTEM_MODULE_ENUMS}) $(patsubst %.hpp,%.pcm,${SYSTEM_MODULE_HEADERS})

SYSTEM_MODULE_DEP = module_build/*.d module_build/src/System/*.d

src/System/System.ixx: $(SYSTEM_MODULE_HEADERS)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_HEADER_UNIT) -c src/System/System.ixx -o src/System/System.o

#src/System/%.cpp : src/System/%.o
#	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_IMP) -fmodule-file=$< -c $< -o $(basename $@.o)
#	echo "-fmodule-file=$< -c $< -o $(basename $@.o)"


System: $(SYSTEM_MODULE_OBJS)
	echo Building module "System"...

# Rule to create Header Units
%.pcm : %.hpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_PCM) $< -o $(basename $@.pcm)

# Module implementation files
module_build/%.o : %.cpp
	mkdir -p ${dir $@}
	$(CXX) $(CPPFLAGS) $(CXXFLAGS_MODULE_IMP) -fmodule-file=$(basename $@.pcm) $< -c -o $@

build/%.o : %.cpp
	mkdir -p ${dir $@}
	$(CXX) -o $@ $< -c $(CPPFLAGS) $(CXXFLAGS)
	
all: $(LIB_OBJS)
	ar -crs $(LIB_PATH) $(LIB_OBJS)
	ranlib $(LIB_PATH)

lib: all

modules: System

.PHONY: clean
clean:
	rm -rf build
	rm -rf gcm.cache

#-include $(LIB_DEP)
-include $(SYSTEM_MODULE_DEP)
