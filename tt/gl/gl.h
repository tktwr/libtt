#pragma once

#if defined(__ANDROID__)
#include <gl3stub.h>
#else
//#include <GL/gl3w.h>
#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#endif

#include <tt/util/type.h>
#include "gl_util.h"

