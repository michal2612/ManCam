enable_testing()

add_executable(core_tests core_pipeline_tests.cpp)

target_link_libraries(core_tests GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(core_tests)