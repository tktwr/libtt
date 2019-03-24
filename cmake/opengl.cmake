#-------------------------------------------------
# OpenGL
#-------------------------------------------------

find_package(OpenGL REQUIRED)

#if(WIN32)
#  set(OPENGL_LIBS glu32 opengl32 winmm gdi32)
#elseif(UNIX)
#  set(OPENGL_LIBS GLU GL)
#endif()

message(STATUS "OPENGL_gl_LIBRARY=${OPENGL_gl_LIBRARY}")
message(STATUS "OPENGL_glu_LIBRARY=${OPENGL_glu_LIBRARY}")
