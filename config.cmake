# config.cmake

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR})
#set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(MINGW)
    set(CMAKE_C_FLAGS "-Wall")
    set(CMAKE_CXX_FLAGS "-Wall")
endif()

# export compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#-------------------------------------------------
# status
#-------------------------------------------------

if(WIN32)
    message(STATUS "OS: WIN32")
elseif(ANDROID)
    message(STATUS "OS: ANDROID")
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

if(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    message(STATUS "CompilerID: MSVC")
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    message(STATUS "CompilerID: Clang")
endif()

message(STATUS "PROJECT_SOURCE_DIR=${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR=${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_SOURCE_DIR=${CMAKE_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR=${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR=${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")
message(STATUS "CMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
message(STATUS "CMAKE_CXX_COMPILER_ID=${CMAKE_CXX_COMPILER_ID}")
message(STATUS "HOME=$ENV{HOME}")
message(STATUS "USERPROFILE=$ENV{USERPROFILE}")

#-------------------------------------------------
# opt
#-------------------------------------------------

if(WIN32)
  set(OPT_DIR $ENV{MY_OPT_WIN})
else()
  set(OPT_DIR $ENV{MY_OPT})
endif()

#-------------------------------------------------
# libtt
#-------------------------------------------------

set(LIBTT ${CMAKE_CURRENT_LIST_DIR})

if(EXISTS ${LIBTT}/local.cmake)
    include(${LIBTT}/local.cmake)
endif()

include(${LIBTT}/cmake/libtt.cmake)

#-------------------------------------------------
# third_party
#-------------------------------------------------

include(${LIBTT}/cmake/glad.cmake)
include(${LIBTT}/cmake/eigen.cmake)
include(${LIBTT}/cmake/glm.cmake)
include(${LIBTT}/cmake/json11.cmake)
include(${LIBTT}/cmake/stb.cmake)
include(${LIBTT}/cmake/opencv.cmake)

include(${LIBTT}/cmake/cereal.cmake)
include(${LIBTT}/cmake/cmdline.cmake)
include(${LIBTT}/cmake/spdlog.cmake)

if(ANDROID)
    include(${LIBTT}/cmake/gl3stub.cmake)
elseif(WIN32)
    include(${LIBTT}/cmake/opengl.cmake)
    include(${LIBTT}/cmake/glfw.cmake)
    include(${LIBTT}/cmake/gl3w.cmake)
    include(${LIBTT}/cmake/imgui.cmake)
    include(${LIBTT}/cmake/nativefiledialog.cmake)
endif()

