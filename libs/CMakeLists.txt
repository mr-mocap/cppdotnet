# Only set the cxx_standard if it is not set by someone else
if (NOT DEFINED CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 20)
endif()

include(System.Base.cmake)
include(System.Collections.cmake)
include(System.IO.cmake)
include(System.Diagnostics.cmake)
include(System.Xml.cmake)