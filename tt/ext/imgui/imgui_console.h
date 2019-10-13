#ifndef imgui_console_h
#define imgui_console_h

#include <imgui.h>
#include <functional>
#include <vector>
#include <string>
#include <stdarg.h>
#include <stdio.h>
#include <sstream>

#if defined(WIN32)
#include <direct.h>
#define popen _popen
#define pclose _pclose
#else
#include <unistd.h>
#endif

class Console {
public:
    Console() {
        m_history_pos = -1;
        m_scroll_to_bottom = true;
    }
    void setFunc(const std::function<void(const std::string& line)>& func) {
        m_func = func;
    }
    void draw();

    void output(const char* fmt, ...) IM_FMTARGS(2);

    void clear() {
        m_text.clear();
    }

    void shell(std::string cmd);

    void addCommand(const std::string& cmd) {
        m_commands.push_back(cmd);
    }

    int TextEditCallback(ImGuiTextEditCallbackData* data);

private:
    std::function<void(const std::string& line)> m_func;
    std::vector<std::string> m_commands;
    std::vector<std::string> m_text;
    std::vector<std::string> m_history;
    std::size_t m_history_pos;
    bool m_scroll_to_bottom;
};

inline int TextEditCallbackStub(ImGuiTextEditCallbackData* data) {
    Console* console = (Console*)data->UserData;
    return console->TextEditCallback(data);
}

inline void Console::draw() {
    const float footer_height_to_reserve = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing(); // 1 separator, 1 input text
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, -footer_height_to_reserve), false, ImGuiWindowFlags_HorizontalScrollbar); // Leave room for 1 separator + 1 InputText
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4,1)); // Tighten spacing
        std::size_t sz = m_text.size();
        for (int i=0; i<sz; i++) {
            ImGui::TextUnformatted(m_text[i].c_str());
        }
        if (m_scroll_to_bottom)
            ImGui::SetScrollHere(1.0f);
        m_scroll_to_bottom = false;
        ImGui::PopStyleVar();
    ImGui::EndChild();

    ImGui::Separator();

    static char input[256];
    bool reclaim_focus = false;
    ImGui::PushItemWidth(-1);
    if (ImGui::InputText("input", input, IM_ARRAYSIZE(input), ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_CallbackCompletion|ImGuiInputTextFlags_CallbackHistory, &TextEditCallbackStub, (void*)this)) {
        m_text.push_back(std::string("> ") + input);
        m_history.push_back(input);
        m_func(input);
        input[0] = '\0';
        m_scroll_to_bottom = true;
        reclaim_focus = true;
    }
    ImGui::PopItemWidth();

    // Demonstrate keeping focus on the input box
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus) {
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
    }
}

inline void Console::output(const char* fmt, ...) {
    char buf[1024];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, IM_ARRAYSIZE(buf), fmt, args);
    buf[IM_ARRAYSIZE(buf)-1] = 0;
    va_end(args);
    m_text.push_back(buf);
    m_scroll_to_bottom = true;
}

inline int   Stricmp(const char* str1, const char* str2)         { int d; while ((d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; } return d; }
inline int   Strnicmp(const char* str1, const char* str2, int n) { int d = 0; while (n > 0 && (d = toupper(*str2) - toupper(*str1)) == 0 && *str1) { str1++; str2++; n--; } return d; }
inline char* Strdup(const char *str)                             { size_t len = strlen(str) + 1; void* buff = malloc(len); return (char*)memcpy(buff, (const void*)str, len); }
inline void  Strtrim(char* str)                                  { char* str_end = str + strlen(str); while (str_end > str && str_end[-1] == ' ') str_end--; *str_end = 0; }

inline int Console::TextEditCallback(ImGuiTextEditCallbackData* data) {
    switch (data->EventFlag) {
    case ImGuiInputTextFlags_CallbackCompletion:
        {
            // Locate beginning of current word
            const char* word_end = data->Buf + data->CursorPos;
            const char* word_start = word_end;
            while (word_start > data->Buf)
            {
                const char c = word_start[-1];
                if (c == ' ' || c == '\t' || c == ',' || c == ';')
                    break;
                word_start--;
            }

            // Build a list of candidates
            ImVector<const char*> candidates;
            for (int i = 0; i < m_commands.size(); i++) {
                /*
                std::string s(word_start, (int)(word_end-word_start));
                if (m_commands[i] == s) {
                    candidates.push_back(m_commands[i].c_str());
                }
                */
                if (Strnicmp(m_commands[i].c_str(), word_start, (int)(word_end-word_start)) == 0) {
                    candidates.push_back(m_commands[i].c_str());
                }
            }

            if (candidates.Size == 0)
            {
                // No match
                output("No match for \"%.*s\"!\n", (int)(word_end-word_start), word_start);
            }
            else if (candidates.Size == 1)
            {
                // Single match. Delete the beginning of the word and replace it entirely so we've got nice casing
                data->DeleteChars((int)(word_start-data->Buf), (int)(word_end-word_start));
                data->InsertChars(data->CursorPos, candidates[0]);
                data->InsertChars(data->CursorPos, " ");
            }
            else
            {
                // Multiple matches. Complete as much as we can, so inputing "C" will complete to "CL" and display "CLEAR" and "CLASSIFY"
                int match_len = (int)(word_end - word_start);
                for (;;)
                {
                    int c = 0;
                    bool all_candidates_matches = true;
                    for (int i = 0; i < candidates.Size && all_candidates_matches; i++)
                        if (i == 0)
                            c = toupper(candidates[i][match_len]);
                        else if (c == 0 || c != toupper(candidates[i][match_len]))
                            all_candidates_matches = false;
                    if (!all_candidates_matches)
                        break;
                    match_len++;
                }

                if (match_len > 0)
                {
                    data->DeleteChars((int)(word_start - data->Buf), (int)(word_end-word_start));
                    data->InsertChars(data->CursorPos, candidates[0], candidates[0] + match_len);
                }

                // List matches
                output("Possible matches:\n");
                for (int i = 0; i < candidates.Size; i++)
                    output("- %s\n", candidates[i]);
            }
            break;
        }
    case ImGuiInputTextFlags_CallbackHistory:
        {
            const std::size_t prev_history_pos = m_history_pos;
            if (data->EventKey == ImGuiKey_UpArrow) {
                if (m_history_pos == -1)
                    m_history_pos = m_history.size() - 1;
                else if (m_history_pos > 0)
                    m_history_pos--;
            } else if (data->EventKey == ImGuiKey_DownArrow) {
                if (m_history_pos != -1)
                    if (++m_history_pos >= m_history.size())
                        m_history_pos = -1;
            }

            if (prev_history_pos != m_history_pos) {
                data->CursorPos = data->SelectionStart = data->SelectionEnd = data->BufTextLen = (int)snprintf(data->Buf, (size_t)data->BufSize, "%s", (m_history_pos >= 0) ? m_history[m_history_pos].c_str() : "");
                data->BufDirty = true;
            }
            break;
        }
    }
    return 0;
}

inline void Console::shell(std::string cmd) {
    std::istringstream istr(cmd);
    std::string token;
    istr >> token;

    if (token == "cd") {
        std::string dir = "~";
        istr >> dir;

        int r = _chdir(dir.c_str());
        if (r) {
            output("sh: cd: %s: No such file or directory\n", dir.c_str());
        }

        return;
    } else if (token == "ls") {
        cmd += " -CF -T 0";
    }

    FILE* fp = popen((cmd+" 2>&1").c_str(), "r");
    const int LINE_SIZE = 1024;
    char data[LINE_SIZE];
    while (fgets(data, LINE_SIZE, fp) != NULL) {
        output("%s", data);
    }
    pclose(fp);
}

#endif  // imgui_console_h

