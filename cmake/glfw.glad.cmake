#-------------------------------------------------
# glad
#-------------------------------------------------

set(GLAD $ENV{MY_OPT_WIN}/glfw/deps)
set(GLAD_SRCS ${GLAD}/glad.c)

include_directories(${GLAD})

message(STATUS "GLAD=${GLAD}")
