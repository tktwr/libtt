#pragma once

#include <tt/window/window_base.h>
#include <tt/ext/imgui/imgui_console.h>
#include <tt/ext/imgui/imgui_util.h>

class StandardWindow : public WindowBase {
public:
    StandardWindow();
    virtual ~StandardWindow() {}

    int create(const std::string& window_title, int width, int height) override;
    void run(std::shared_ptr<AppBase> app) override;
    void close() override;

    virtual void drawGui();
    virtual void drawGuiMainMenuBar();
    virtual void drawGuiControlPanel();
    virtual void drawGuiConsolePanel();

    void registerCommands();

    void cmd_quit();
    void cmd_clear();
    void cmd_help();

    void command(const std::string& line);

    struct Command {
        std::string name;
        std::string args;
        std::string desc;
    };

protected:
    std::vector<Command> m_commands;

    bool m_show_main_menu_bar = true;
    bool m_show_control_panel = true;
    bool m_show_console_panel = true;

    Console m_console;
    int m_console_size[2] = {600, 400};
};
