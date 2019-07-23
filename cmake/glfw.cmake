#-------------------------------------------------
# glfw
#-------------------------------------------------

set(GLFW $ENV{MY_OPT_WIN}/glfw)

if(MSVC)
  include_directories(${GLFW}/include)
  link_directories(${GLFW}/build.vs2019/src/Release)
endif()

set(GLFW_LIBS glfw3)
#if(MSVC)
#  set(GLFW_LIBS glfw3 legacy_stdio_definitions)
#elseif(MINGW)
#  set(GLFW_LIBS glfw3)
#endif()

message(STATUS "GLFW=${GLFW}")
