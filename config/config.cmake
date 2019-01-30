# config.cmake

set(OPENCV Z:/opt/opencv-3.4.3/build)
set(GLFW Z:/opt/glfw)
set(GLAD Z:/opt/glfw/deps)
set(IMGUI Z:/opt/imgui)
set(GL3W ${IMGUI}/examples/libs/gl3w)

set(GLM Z:/opt/glm)
set(STB Z:/opt/stb)
set(NFD Z:/opt/nativefiledialog/src)

set(SPDLOG Z:/opt/spdlog)
set(CEREAL Z:/opt/cereal)
set(CMDLINE Z:/opt/cmdline)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()

#-------------------------------------------------
# compiler flags

if(MINGW)
  set(CMAKE_C_FLAGS "-static -Wall")
  set(CMAKE_CXX_FLAGS "-static -Wall")
endif()

#-------------------------------------------------
# include

include_directories(${GLM})
include_directories(${STB})
include_directories(${SPDLOG}/include)
include_directories(${CEREAL}/include)
include_directories(${CMDLINE})

#-------------------------------------------------
# gl3w

include_directories(${GL3W})
set(GL3W_SRCS ${GL3W}/GL/gl3w.c)

#-------------------------------------------------
# glad

include_directories(${GLAD})
set(GLAD_SRCS ${GLAD}/glad.c)

#-------------------------------------------------
# glfw

if(MSVC)
  include_directories(${GLFW}/include)
  link_directories(${GLFW}/build/src/Release)
endif()

set(GLFW_LIBS glfw3)

#if(MSVC)
#  set(GLFW_LIBS glfw3 legacy_stdio_definitions)
#elseif(MINGW)
#  set(GLFW_LIBS glfw3)
#endif()

#-------------------------------------------------
# imgui

include_directories(${IMGUI})
include_directories(${IMGUI}/examples)
set(IMGUI_SRCS
  ${IMGUI}/imgui.cpp
  ${IMGUI}/imgui_draw.cpp
  ${IMGUI}/imgui_widgets.cpp
  ${IMGUI}/examples/imgui_impl_glfw.cpp
  ${IMGUI}/examples/imgui_impl_opengl3.cpp
  )

#-------------------------------------------------
# nativefiledialog

include_directories(${NFD}/include)
set(NFD_SRCS
  ${NFD}/nfd_common.c
  ${NFD}/nfd_win.cpp
  )

#-------------------------------------------------
# OpenGL

find_package(OpenGL REQUIRED)

#if(WIN32)
#  set(OPENGL_LIBS glu32 opengl32 winmm gdi32)
#elseif(UNIX)
#  set(OPENGL_LIBS GLU GL)
#endif()

#-------------------------------------------------
# OpenCV

if(MSVC)
  set(OpenCV_DIR ${OPENCV})
  file(GLOB OpenCV_DLLS ${OPENCV}/x64/vc15/bin/*.dll)
endif()

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

#-------------------------------------------------
# libtt

include_directories(${LIBTT})
set(LIBTT_SRCS
  ${LIBTT}/tt/util/filename.cpp
  ${LIBTT}/tt/util/path.cpp
  ${LIBTT}/tt/gfx/imagex.cpp
  ${LIBTT}/tt/gfx/image_util.cpp
  ${LIBTT}/tt/gl/gl_fbo.cpp
  ${LIBTT}/tt/gl/gl_frame.cpp
  ${LIBTT}/tt/gl/gl_frame_display.cpp
  ${LIBTT}/tt/gl/gl_program.cpp
  ${LIBTT}/tt/gl/gl_texture.cpp
  ${LIBTT}/tt/gl/gl_vao.cpp
  ${LIBTT}/tt/app/gl_app.cpp
  )

#-------------------------------------------------
# status

if(WIN32)
  message(STATUS "OS: WIN32")
elseif(UNIX)
  message(STATUS "OS: UNIX")
endif()

if(MSVC)
  message(STATUS "Compiler: MSVC")
elseif(MINGW)
  message(STATUS "Compiler: MINGW")
else()
  message(STATUS "Compiler: other")
endif()

message(STATUS "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "INCLUDE_DIRECTORIES=${INCLUDE_DIRECTORIES}")
message(STATUS "LINK_DIRECTORIES=${LINK_DIRECTORIES}")

message(STATUS "OPENGL_INCLUDE_DIR=${OPENGL_INCLUDE_DIR}")
message(STATUS "OPENGL_gl_LIBRARY=${OPENGL_gl_LIBRARY}")
message(STATUS "OPENGL_glu_LIBRARY=${OPENGL_glu_LIBRARY}")

message(STATUS "OpenCV_VERSION=${OpenCV_VERSION}")
message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
message(STATUS "OpenCV_SHARED=${OpenCV_SHARED}")
message(STATUS "OpenCV_STATIC=${OpenCV_STATIC}")
message(STATUS "OpenCV_CUDA=${OpenCV_CUDA}")
message(STATUS "OpenCV_DLLS=${OpenCV_DLLS}")

