#pragma once

#include <string>
#include <vector>
#include <array>
#include <tt/util/type.h>
#include <tt/gfx/image.h>
#include <tt/gfx/image_util.h>
#include <tt/gl/gl.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <tt/ext/imgui/imgui_console.h>
#include <tt/ext/imgui/imgui_util.h>

class GLApp {
public:
    enum UiType {
        UI_CUI = 0,
        UI_GUI,
    };

    struct Command {
        std::string name;
        std::string args;
        std::string desc;
    };

    GLApp();
    virtual ~GLApp();

    int w() const { return m_window_size[0]; }
    int h() const { return m_window_size[1]; }

    void setWindowTitle(const std::string& s) { m_window_title = s; }
    void setWindowSize(int w, int h) { m_window_size[0] = w; m_window_size[1] = h; }
    void setIconFile(const std::string& fname) { m_icon_file = fname; }
    void setDataDir(const std::string& dir) { m_data_dir = dir; }
    std::string getDataDir() const { return m_data_dir; }

    void run();

    void setUiType(UiType ui) { m_ui = ui; }

    void registerCommands();

    void cmd_quit();
    void cmd_clear();
    void cmd_help();

    void drawGuiConsolePanel();

protected:
    void setIcon(const std::string& fname);

    void runCui();
    void runGui();

    virtual void exec(const std::string& line);

    virtual void setup();
    virtual void mainLoop();
    virtual void shutdown();

    virtual void init() {}
    virtual void drawGui();
    virtual void draw() {}

    GLFWwindow* m_window;
    Console m_console;

    UiType m_ui = UI_GUI;

    std::vector<Command> m_commands;

    std::string m_window_title;
    std::string m_icon_file;
    std::string m_data_dir;

    tt::Vec2i m_window_size = {800, 600};
    tt::Vec2i m_console_size = {600, 400};
    bool m_show_console_panel = true;
};

std::string f_open_file();
std::string f_save_file();

