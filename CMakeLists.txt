cmake_minimum_required(VERSION 3.6)

project(libtt)

include(config.cmake)

add_library(tt STATIC ${LIBTT_SRCS})
install(TARGETS tt ARCHIVE DESTINATION lib)

add_subdirectory(test)

