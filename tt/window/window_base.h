#pragma once

#include <string>
#include <memory>
#include <tt/app/app_base.h>

class GLFWwindow;

class WindowBase {
public:
    WindowBase() {}
    virtual ~WindowBase() {}

    virtual int  create(const std::string& window_title, int width, int height);
    virtual void run(std::shared_ptr<AppBase> app);
    virtual void close();

    std::shared_ptr<AppBase> app();

protected:
    GLFWwindow* m_window = nullptr;
};

