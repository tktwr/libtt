#include "gl_app.h"
#include <nfd.h>
#include <stdio.h>
#include <string>

std::string f_open_file() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_OpenDialog(NULL, NULL, &outPath);

    std::string str;
    if ( result == NFD_OKAY ) {
        str = std::string(outPath);
        puts("Success!");
        puts(outPath);
        free(outPath);
    } else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    } else {
        printf("Error: %s\n", NFD_GetError() );
    }

    return str;
}

std::string f_save_file() {
    nfdchar_t *outPath = NULL;
    nfdresult_t result = NFD_SaveDialog(NULL, NULL, &outPath);

    std::string str;
    if ( result == NFD_OKAY ) {
        str = std::string(outPath);
        puts("Success!");
        puts(outPath);
        free(outPath);
    } else if ( result == NFD_CANCEL ) {
        puts("User pressed cancel.");
    } else {
        printf("Error: %s\n", NFD_GetError() );
    }

    return str;
}

static void glfw_error_callback(int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

GLApp::GLApp() {
    m_window_title = "GLApp";
    m_window = 0;
}

GLApp::~GLApp() {
}

void GLApp::setIcon(const std::string& fname) {
    tt::Image4uc image;
    bool b = f_load_image(fname, image);
    if (!b) return;

    GLFWimage glfw_image;
    glfw_image.width  = image.w();
    glfw_image.height = image.h();
    glfw_image.pixels = reinterpret_cast<unsigned char*>(image.data());

    glfwSetWindowIcon(m_window, 1, &glfw_image);
}

void GLApp::runCui() {
    std::string line;
    while (1) {
        std::cout << "> " << std::flush;
        if (!std::getline(std::cin, line)) return;
        if (line == "quit") return;
        if (line == "") continue;
        if (line[0] == '#') continue;
        exec(line);
    }
}

void GLApp::runGui() {
    setup();
    mainLoop();
    shutdown();
}

void GLApp::run() {
    if (m_ui == UI_CUI) {
        runCui();
    } else if (m_ui == UI_GUI) {
        runGui();
    }
}

void GLApp::setup() {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        return;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    m_window = glfwCreateWindow(m_window_size[0], m_window_size[1], m_window_title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(m_window);
    glfwSwapInterval(1); // Enable vsync

    //gl3wInit();
    gladLoadGL();

    // Setup Dear ImGui binding
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls

    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    ImGui_ImplOpenGL3_Init();

    // Setup style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    setIcon(getDataDir() + m_icon_file);
}

void GLApp::mainLoop() {
    init();

    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        // Start the ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        drawGui();

        // Rendering
        ImGui::Render();
        glfwMakeContextCurrent(m_window);
        glfwGetFramebufferSize(m_window, &m_window_size[0], &m_window_size[1]);

        draw();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwMakeContextCurrent(m_window);
        glfwSwapBuffers(m_window);
    }
}

void GLApp::shutdown() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();
}

void GLApp::registerCommands() {
    std::size_t sz = m_commands.size();
    for (int i=0; i<sz; i++) {
        Command& cmd = m_commands[i];
        m_console.addCommand(cmd.name);
    }

    m_console.setFunc([&](const std::string& line) {
        exec(line);
    });
}

void GLApp::cmd_quit() {
    glfwSetWindowShouldClose(m_window, 1);
}

void GLApp::cmd_clear() {
    m_console.clear();
}

void GLApp::cmd_help() {
    std::size_t sz = m_commands.size();
    for (int i=0; i<sz; i++) {
        Command& cmd = m_commands[i];
        m_console.output("%s %s ... %s", cmd.name.c_str(), cmd.args.c_str(), cmd.desc.c_str());
    }
}

void GLApp::exec(const std::string& line) {
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
        if (line.size()) {
            m_console.shell(line);
        }
    }
}

void GLApp::drawGuiConsolePanel() {
    ImGui::SetNextWindowSize(toImVec2(m_console_size), ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_FirstUseEver);
    ImGui::Begin("Console", &m_show_console_panel);
    m_console.draw();
    ImGui::End();
}

void GLApp::drawGui() {
    if (m_show_console_panel) drawGuiConsolePanel();
}

