#-------------------------------------------------
# gl3w
#-------------------------------------------------

set(GL3W $ENV{MY_OPT_WIN}/imgui/examples/libs/gl3w)
set(GL3W_SRCS ${GL3W}/GL/gl3w.c)

include_directories(${GL3W})

message(STATUS "GL3W=${GL3W}")
