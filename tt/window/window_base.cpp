#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <tt/util/log.h>

#include "window_base.h"

std::shared_ptr<AppBase> g_app = nullptr;

std::shared_ptr<AppBase> WindowBase::app() {
    return g_app;
}

void drop_callback(GLFWwindow* window, int count, const char** paths) {
    std::vector<std::string> fnames;
    for (int i = 0; i < count; i++) fnames.push_back(paths[i]);
    if (g_app) g_app->dropFiles(fnames);
}

void window_size_callback(GLFWwindow* window, int width, int height) {
    if (g_app) g_app->setScreenSize(width, height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    //tt::Log::I("key_callback: key=%d scancode=%d action=%d mods=%d\n", key, scancode, action, mods);

    switch (action) {
        case GLFW_PRESS:
            {
                switch (key) {
                    case GLFW_KEY_ESCAPE:
                        glfwSetWindowShouldClose(window, GLFW_TRUE);
                        break;
                    default:
                        if (g_app) g_app->keyDown(key);
                        break;
                }
            }
            break;
        case GLFW_RELEASE:
            if (g_app) g_app->keyUp(key);
            break;
        case GLFW_REPEAT:
            if (g_app) g_app->keyRepeat(key);
            break;
    }
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    //tt::Log::I("mouse_button_callback: button=%d action=%d mods=%d\n", button, action, mods);

    if (button != GLFW_MOUSE_BUTTON_LEFT) return;

    switch (action) {
        case GLFW_PRESS:
            {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                if (g_app) g_app->touchDown(static_cast<float>(x), static_cast<float>(y));
            }
            break;
        case GLFW_RELEASE:
            {
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                if (g_app) g_app->touchUp(static_cast<float>(x), static_cast<float>(y));
            }
            break;
    }
}

void cursor_position_callback(GLFWwindow* window, double x, double y) {
    //tt::Log::I("cursor_position_callback: x=%lf y=%lf\n", x, y);

    static double prev_x = -1;
    static double prev_y = -1;

    if (prev_x == -1 && prev_y == -1) {
        prev_x = x;
        prev_y = y;
    }

    int action = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
    switch (action) {
        case GLFW_PRESS:
            {
                double dx = x - prev_x;
                double dy = y - prev_y;
                if (g_app) g_app->touchMove(static_cast<float>(dx), static_cast<float>(dy));
            }
            break;
    }

    prev_x = x;
    prev_y = y;
}

int WindowBase::create(const std::string& window_title, int width, int height) {
    if (!glfwInit()) {
        return -1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(width, height, window_title.c_str(), NULL, NULL);
    if (!m_window) {
        glfwTerminate();
        return -1;
    }

    glfwSetDropCallback(m_window, drop_callback);
    glfwSetWindowSizeCallback(m_window, window_size_callback);
    glfwSetKeyCallback(m_window, key_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetCursorPosCallback(m_window, cursor_position_callback);

    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1);

    gladLoadGL();

    return 0;
}

void WindowBase::run(std::shared_ptr<AppBase> app) {
    if (!app) return;

    g_app = app;
    if (g_app) {
        int framebuffer_size[2];
        glfwGetFramebufferSize(m_window, &framebuffer_size[0], &framebuffer_size[1]);

        g_app->Init();
        g_app->setScreenSize(framebuffer_size[0], framebuffer_size[1]);
    }

    tt::Time tm;
    tm.start();

    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        if (g_app) {
            tm.end();
            g_app->setTime(tm.getElapsedMSec());
            g_app->Draw();
        }

        glfwSwapBuffers(m_window);
    }
}

void WindowBase::close() {
    glfwDestroyWindow(m_window);
    glfwTerminate();
}

