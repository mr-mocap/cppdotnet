cmake_minimum_required(VERSION 3.28)

set(CMAKE_CXX_STANDARD "20" CACHE STRING "C++ standard for cppdotnet libraries")
set(_CPPDOTNET_VALID_CXX "20;23;26")
if (NOT CMAKE_CXX_STANDARD IN_LIST _CPPDOTNET_VALID_CXX)
    message(FATAL ERROR "Invalid CMAKE_CXX_STANDARD: ${CMAKE_CXX_STANDARD}.  Valid values: ${_CPPDOTNET_VALID_CXX }")
endif()

project(cppdotnet
        VERSION 0.1.0
        DESCRIPTION "A Sample Implementatioon of .NET libraries"
        LANGUAGES CXX C)

add_subdirectory(libs)
add_subdirectory(testing)