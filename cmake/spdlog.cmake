#-------------------------------------------------
# spdlog
#-------------------------------------------------

set(SPDLOG $ENV{MY_OPT}/spdlog)

include_directories(${SPDLOG}/include)

message(STATUS "SPDLOG=${SPDLOG}")
