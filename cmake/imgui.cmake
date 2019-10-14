#-------------------------------------------------
# imgui
#-------------------------------------------------

set(IMGUI ${OPT_DIR}/imgui)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

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
