#include <glad/glad.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <tt/util/log.h>
#include <tt/util/time.h>
#include <tt/ext/nfd/nfd_util.h>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include "StandardWindow.h"

extern std::shared_ptr<AppBase> g_app;

StandardWindow::StandardWindow() {
    m_commands = {
        {"help",              "",                   "print help"},
        {"clear",             "",                   "clear console"},
        {"quit",              "",                   "exit the program"},
    };

    registerCommands();
}

int StandardWindow::create(const std::string& window_title, int width, int height) {
    WindowBase::create(window_title, width, height);

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();

    return 0;
}

void StandardWindow::run(std::shared_ptr<AppBase> app) {
    if (!app) return;

    int window_size[2];
    glfwGetWindowSize(m_window, &window_size[0], &window_size[1]);
    tt::Log::I("window size: %d %d\n", window_size[0], window_size[1]);

    int left, top, right, bottom;
    glfwGetWindowFrameSize(m_window, &left, &top, &right, &bottom);
    tt::Log::I("window frame size: %d %d %d %d\n", left, top, right, bottom);

    int framebuffer_size[2];
    glfwGetFramebufferSize(m_window, &framebuffer_size[0], &framebuffer_size[1]);
    tt::Log::I("framebuffer size: %d %d\n", framebuffer_size[0], framebuffer_size[1]);

    g_app = app;
    if (g_app) {
        g_app->Init();
        g_app->setScreenSize(framebuffer_size[0], framebuffer_size[1]);
    }

    tt::Time tm;
    tm.start();

    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        drawGui();

        // Rendering
        ImGui::Render();

        if (g_app) {
            tm.end();
            g_app->setTime(tm.getElapsedMSec());
            g_app->Draw();
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(m_window);
    }
}

void StandardWindow::close() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    WindowBase::close();
}

void StandardWindow::drawGui() {
    if (m_show_main_menu_bar) drawGuiMainMenuBar();
    if (m_show_control_panel) drawGuiControlPanel();
    if (m_show_console_panel) drawGuiConsolePanel();
}

void StandardWindow::drawGuiMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Open...")) {
                std::string fname = f_open_file();
                if (fname != "") {
                    if (g_app) g_app->command("load " + fname);
                }
            }
            if (ImGui::MenuItem("Save As...")) {
                std::string fname = f_save_file();
                if (fname != "") {
                    if (g_app) g_app->command("save " + fname);
                }
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "CTRL+Q")) {
                glfwSetWindowShouldClose(m_window, 1);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View")) {
            ImGui::MenuItem("Main Menu Bar", "CTRL+M", &m_show_main_menu_bar);
            ImGui::MenuItem("Control", NULL, &m_show_control_panel);
            ImGui::MenuItem("Console", NULL, &m_show_console_panel);
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help")) {
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void StandardWindow::drawGuiControlPanel() {
    ImGui::Begin("Control Panel", &m_show_control_panel);
    if (ImGui::Button("Button")) {
    }
    if (g_app) {
        ImGui::Text("time: %.2f msec", g_app->getTime());
        ImGui::Text("init_time: %.2f msec", g_app->getInitTime());
        ImGui::Text("draw_time: %.2f msec", g_app->getDrawTime());
    }

    ImGui::End();
}

void StandardWindow::drawGuiConsolePanel() {
    ImGui::SetNextWindowSize(toImVec2(m_console_size), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("Console", &m_show_console_panel);
    m_console.draw();
    ImGui::End();
}

void StandardWindow::registerCommands() {
    std::size_t sz = m_commands.size();
    for (int i=0; i<sz; i++) {
        Command& cmd = m_commands[i];
        m_console.addCommand(cmd.name);
    }

    m_console.setFunc([&](const std::string& line) {
        command(line);
    });
}

void StandardWindow::cmd_quit() {
    glfwSetWindowShouldClose(m_window, 1);
}

void StandardWindow::cmd_clear() {
    m_console.clear();
}

void StandardWindow::cmd_help() {
    std::size_t sz = m_commands.size();
    for (int i=0; i<sz; i++) {
        Command& cmd = m_commands[i];
        m_console.output("%s %s ... %s", cmd.name.c_str(), cmd.args.c_str(), cmd.desc.c_str());
    }
}

void StandardWindow::command(const std::string& line) {
    std::istringstream is(line);
    std::string token;

    is >> token;

    if (token == "") return;
    if (token[0] == '#') return;
    if (token == "quit") {
        cmd_quit();
    } else if (token == "help") {
        cmd_help();
    } else if (token == "clear") {
        cmd_clear();
    } else {
        bool b = false;
        if (g_app) {
            b = g_app->command(line);
        }
        if (!b && line.size()) {
            m_console.shell(line);
        }
    }
}

