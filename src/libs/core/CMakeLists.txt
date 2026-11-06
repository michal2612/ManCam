add_library(core)
file(GLOB SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cppm)
target_sources(core PUBLIC FILE_SET CXX_MODULES FILES ${SRC_FILES})