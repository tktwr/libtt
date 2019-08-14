#-------------------------------------------------
# json11
#-------------------------------------------------

set(JSON11 ${OPT_DIR}/json11)
set(JSON11_SRCS ${JSON11}/json11.cpp)

include_directories(${JSON11})

message(STATUS "JSON11=${JSON11}")
