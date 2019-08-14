#-------------------------------------------------
# glad
#-------------------------------------------------

set(GLAD ${OPT_DIR}/glfw/deps)
set(GLAD_SRCS ${GLAD}/glad.c)

include_directories(${GLAD})

message(STATUS "GLAD=${GLAD}")
