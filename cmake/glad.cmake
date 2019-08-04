#-------------------------------------------------
# glad
#-------------------------------------------------

set(GLAD $ENV{MY_LIBTT_WIN}/third_party/glad)
set(GLAD_SRCS ${GLAD}/src/glad.c)

include_directories(${GLAD}/include)

message(STATUS "GLAD=${GLAD}")
