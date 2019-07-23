#-------------------------------------------------
# json11
#-------------------------------------------------

set(JSON11 $ENV{MY_OPT_WIN}/json11)
set(JSON11_SRCS ${JSON11}/json11.cpp)

include_directories(${JSON11})

message(STATUS "JSON11=${JSON11}")
