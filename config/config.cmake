# config.cmake

if ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MINGW)
  set(CMAKE_C_FLAGS "-static -Wall")
  set(CMAKE_CXX_FLAGS "-static -Wall")
endif()

#-------------------------------------------------
# glm
set(GLM $ENV{MY_OPT}/glm)
message(STATUS "GLM=${GLM}")

include_directories(${GLM})
#-------------------------------------------------
# stb
set(STB $ENV{MY_OPT}/stb)
message(STATUS "STB=${STB}")

include_directories(${STB})
#-------------------------------------------------
# spdlog
set(SPDLOG $ENV{MY_OPT}/spdlog)
message(STATUS "SPDLOG=${SPDLOG}")

include_directories(${SPDLOG}/include)
#-------------------------------------------------
# cereal
set(CEREAL $ENV{MY_OPT}/cereal)
message(STATUS "CEREAL=${CEREAL}")

include_directories(${CEREAL}/include)
#-------------------------------------------------
# cmdline
set(CMDLINE $ENV{MY_OPT}/cmdline)
message(STATUS "CMDLINE=${CMDLINE}")

include_directories(${CMDLINE})
#-------------------------------------------------
# glad
set(GLAD $ENV{MY_OPT}/glfw/deps)
message(STATUS "GLAD=${GLAD}")

include_directories(${GLAD})
set(GLAD_SRCS ${GLAD}/glad.c)
#-------------------------------------------------
# glfw
set(GLFW $ENV{MY_OPT}/glfw)
message(STATUS "GLFW=${GLFW}")

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
set(IMGUI $ENV{MY_OPT}/imgui)
message(STATUS "IMGUI=${IMGUI}")

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
# gl3w
set(GL3W $ENV{MY_OPT}/imgui/examples/libs/gl3w)
message(STATUS "GL3W=${GL3W}")

include_directories(${GL3W})
set(GL3W_SRCS ${GL3W}/GL/gl3w.c)
#-------------------------------------------------
# nativefiledialog
set(NFD $ENV{MY_OPT}/nativefiledialog/src)
message(STATUS "NFD=${NFD}")

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

message(STATUS "OPENGL_gl_LIBRARY=${OPENGL_gl_LIBRARY}")
message(STATUS "OPENGL_glu_LIBRARY=${OPENGL_glu_LIBRARY}")
#-------------------------------------------------
# OpenCV
set(OPENCV $ENV{MY_OPT}/opencv-3.4.3/build)
message(STATUS "OPENCV=${OPENCV}")

if(MSVC)
  set(OpenCV_DIR ${OPENCV})
  file(GLOB OpenCV_DLLS ${OPENCV}/x64/vc15/bin/*.dll)
endif()
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

message(STATUS "OpenCV_VERSION=${OpenCV_VERSION}")
message(STATUS "OpenCV_INCLUDE_DIRS=${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS=${OpenCV_LIBS}")
message(STATUS "OpenCV_SHARED=${OpenCV_SHARED}")
message(STATUS "OpenCV_STATIC=${OpenCV_STATIC}")
message(STATUS "OpenCV_CUDA=${OpenCV_CUDA}")
message(STATUS "OpenCV_DLLS=${OpenCV_DLLS}")
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

