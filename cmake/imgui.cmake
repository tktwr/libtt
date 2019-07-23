#-------------------------------------------------
# imgui
#-------------------------------------------------

set(IMGUI $ENV{MY_OPT_WIN}/imgui)

include_directories(${IMGUI})
include_directories(${IMGUI}/examples)

set(IMGUI_SRCS
  ${IMGUI}/imgui.cpp
  ${IMGUI}/imgui_draw.cpp
  ${IMGUI}/imgui_widgets.cpp
  ${IMGUI}/examples/imgui_impl_glfw.cpp
  ${IMGUI}/examples/imgui_impl_opengl3.cpp
)

message(STATUS "IMGUI=${IMGUI}")
