#-------------------------------------------------
# libtt
#-------------------------------------------------

add_definitions(-DNOMINMAX)
add_definitions(-D_USE_MATH_DEFINES)
add_definitions(-DUSE_GLAD)

include_directories(${LIBTT})
set(LIBTT_SRCS
  ${LIBTT}/tt/util/filename.cpp
  ${LIBTT}/tt/util/log.cpp
  ${LIBTT}/tt/gfx/imagex.cpp
  ${LIBTT}/tt/gfx/image_util.cpp
  ${LIBTT}/tt/gfx/mesh.cpp
  ${LIBTT}/tt/gfx/fmt/obj.cpp
  ${LIBTT}/tt/gl/gl_fbo.cpp
  ${LIBTT}/tt/gl/gl_frame.cpp
  ${LIBTT}/tt/gl/gl_frame_display.cpp
  ${LIBTT}/tt/gl/gl_program.cpp
  ${LIBTT}/tt/gl/gl_texture.cpp
  ${LIBTT}/tt/gl/gl_vao.cpp
  ${LIBTT}/tt/gl/gl_vao_mesh.cpp
)
set(LIBTT_PC_SRCS
  ${LIBTT}/tt/window/window_base.cpp
  ${LIBTT}/tt/ext/nfd/nfd_util.cpp
)
set(LIBTT_PC_EXT_SRCS
  ${LIBTT}/tt/ext/opencv/opencv_util.cpp
  ${LIBTT}/tt/ext/pc/gl_app.cpp
  ${LIBTT}/tt/ext/win/path.cpp
)

message(STATUS "LIBTT=${LIBTT}")
