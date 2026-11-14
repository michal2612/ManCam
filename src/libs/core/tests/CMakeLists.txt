file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)
add_executable(core_tests ${SRC_FILES})

target_link_libraries(core_tests PRIVATE GTest::gtest_main)
target_link_libraries(core_tests PRIVATE core)

include(GoogleTest)
gtest_discover_tests(core_tests)