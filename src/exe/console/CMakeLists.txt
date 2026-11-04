add_executable(console)
target_sources(console PRIVATE main.cpp)
target_link_libraries(console PRIVATE core)