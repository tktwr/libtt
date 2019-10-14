#-------------------------------------------------
# gl3stub
#-------------------------------------------------

set(GL3STUB ${LIBTT}/third_party/gl3stub)
set(GL3STUB_SRCS ${GL3STUB}/gl3stub.c)

include_directories(${GL3STUB})

message(STATUS "GL3STUB=${GL3STUB}")
