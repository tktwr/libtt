#-------------------------------------------------
# imgui
#-------------------------------------------------

set(IMGUI ${OPT_DIR}/imgui)

add_definitions(-DIMGUI_IMPL_OPENGL_LOADER_GLAD)

include_directories(${IMGUI})
include_directories(${IMGUI}/backends)

set(IMGUI_SRCS
  ${IMGUI}/imgui.cpp
  ${IMGUI}/imgui_draw.cpp
  ${IMGUI}/imgui_widgets.cpp
  ${IMGUI}/imgui_tables.cpp
  ${IMGUI}/backends/imgui_impl_glfw.cpp
  ${IMGUI}/backends/imgui_impl_opengl3.cpp
)

message(STATUS "IMGUI=${IMGUI}")
