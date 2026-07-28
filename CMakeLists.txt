cmake_minimum_required(VERSION 3.28)

if (NOT DEFINED CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD "20" CACHE STRING "C++ standard to compile against")
endif()

set(_CPPDOTNET_VALID_CXX "20;23;26")
if (NOT CMAKE_CXX_STANDARD IN_LIST _CPPDOTNET_VALID_CXX)
    message(FATAL ERROR "Invalid CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}.  Valid values: ${_CPPDOTNET_VALID_CXX }")
endif()

set(CXX_STANDARD_REQUIRED ON)
set(CXX_EXTENSIONS OFF)

project(cppdotnet
        VERSION 0.1.0
        DESCRIPTION "A Sample Implementatioon of .NET libraries"
        LANGUAGES CXX C)

add_subdirectory(libs)
add_subdirectory(testing)