cmake_minimum_required(VERSION 3.6)

project(libtt)

include(config.cmake)

add_library(tt STATIC ${LIBTT_SRCS})

if(ANDROID)
target_link_libraries(tt GLESv3 EGL log)
endif()

install(TARGETS tt ARCHIVE DESTINATION lib)

add_subdirectory(test)

