#pragma once

#include <string>
#include <tt/app/app_base.h>
#include <memory>

class GLFWwindow;

class WindowBase {
public:
    WindowBase() {}
    virtual ~WindowBase() {}

    virtual int  create(const std::string& window_title, int width, int height);
    virtual void run(std::shared_ptr<AppBase> app);
    virtual void close();

protected:
    GLFWwindow* m_window = nullptr;
};

