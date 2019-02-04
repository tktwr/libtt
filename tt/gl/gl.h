#ifndef gl_h
#define gl_h

#define NOMINMAX 1

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <tt/util/type.h>

inline void glClearColor4f(const float v[4]) {
    glClearColor(v[0], v[1], v[2], v[3]);
}

#endif  // gl_h

