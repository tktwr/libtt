cmake_minimum_required(VERSION 3.8)

project(libtt CXX)

include(config.cmake)

add_library(tt STATIC ${LIBTT_SRCS})
install(TARGETS tt ARCHIVE DESTINATION lib)

add_executable(test_array
    test/test_array.cpp
    ${LIBTT}/tt/util/log.cpp
    )
target_link_libraries(test_array)

add_executable(test_image
    test/test_image.cpp
    ${LIBTT}/tt/util/log.cpp
    )
target_link_libraries(test_image)

add_executable(test_util
    test/test_util.cpp
    ${LIBTT}/tt/util/log.cpp
    )
target_link_libraries(test_util)

