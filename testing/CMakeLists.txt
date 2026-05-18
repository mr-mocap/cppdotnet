add_executable(TestActivity TestActivity.cpp)
target_link_libraries(TestActivity PRIVATE cppdotnet_base)
target_include_directories(TestActivity PRIVATE ${PROJECT_SOURCE_DIR}/libs/include)

add_executable(TestActivitySource TestActivitySource.cpp)
target_link_libraries(TestActivitySource PRIVATE cppdotnet_diagnostics cppdotnet_xml cppdotnet_io cppdotnet_collections cppdotnet_base)
target_include_directories(TestActivitySource PRIVATE ${PROJECT_SOURCE_DIR}/libs/include)

enable_testing()

add_test(NAME TestActivity COMMAND TestActivity)
add_test(NAME TestActivitySource COMMAND TestActivitySource)