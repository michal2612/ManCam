add_executable(core_tests core_pipeline_tests.cpp)

target_link_libraries(core_tests PRIVATE GTest::gtest_main)
target_link_libraries(core_tests PRIVATE core)

include(GoogleTest)
gtest_discover_tests(core_tests)