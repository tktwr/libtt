#-------------------------------------------------
# libtt
#-------------------------------------------------

include_directories(${LIBTT})
set(LIBTT_SRCS
  ${LIBTT}/tt/util/filename.cpp
  ${LIBTT}/tt/util/log.cpp
  ${LIBTT}/tt/gfx/imagex.cpp
  ${LIBTT}/tt/gfx/image_util.cpp
  ${LIBTT}/tt/gl/gl_fbo.cpp
  ${LIBTT}/tt/gl/gl_frame.cpp
  ${LIBTT}/tt/gl/gl_frame_display.cpp
  ${LIBTT}/tt/gl/gl_program.cpp
  ${LIBTT}/tt/gl/gl_texture.cpp
  ${LIBTT}/tt/gl/gl_vao.cpp
)
set(LIBTT_PC_SRCS
  ${LIBTT}/tt/ext/pc/gl_app.cpp
  ${LIBTT}/tt/ext/opencv/opencv_util.cpp
  ${LIBTT}/tt/ext/win/path.cpp
)

message(STATUS "LIBTT=${LIBTT}")
