#-------------------------------------------------
# spdlog
#-------------------------------------------------

set(SPDLOG $ENV{MY_OPT_WIN}/spdlog)

include_directories(${SPDLOG}/include)

message(STATUS "SPDLOG=${SPDLOG}")
