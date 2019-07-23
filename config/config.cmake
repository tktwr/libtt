# config.cmake

if (NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MINGW)
  #set(CMAKE_C_FLAGS "-static -Wall -Wl,--allow-multiple-definition")
  #set(CMAKE_CXX_FLAGS "-static -Wall -Wl,--allow-multiple-definition")
  set(CMAKE_C_FLAGS "-Wall")
  set(CMAKE_CXX_FLAGS "-Wall")
endif()

#-------------------------------------------------
# libtt
#-------------------------------------------------

set(LIBTT $ENV{MY_LIBTT_WIN})

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
# third_party
#-------------------------------------------------

include(${LIBTT}/cmake/cereal.cmake)
include(${LIBTT}/cmake/cmdline.cmake)
include(${LIBTT}/cmake/eigen.cmake)
include(${LIBTT}/cmake/gl3w.cmake)
include(${LIBTT}/cmake/glad.cmake)
include(${LIBTT}/cmake/glfw.cmake)
include(${LIBTT}/cmake/glm.cmake)
include(${LIBTT}/cmake/imgui.cmake)
include(${LIBTT}/cmake/json11.cmake)
include(${LIBTT}/cmake/nativefiledialog.cmake)
include(${LIBTT}/cmake/opencv.cmake)
include(${LIBTT}/cmake/opengl.cmake)
include(${LIBTT}/cmake/spdlog.cmake)
include(${LIBTT}/cmake/stb.cmake)

#-------------------------------------------------
# status
#-------------------------------------------------

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

