#ifndef imgui_util_h
#define imgui_util_h

#include <vector>
#include <string>
#include <string.h>
#include <imgui.h>

class ArrayOfString {
public:
    ArrayOfString(const std::vector<std::string>& vec) { setVector(vec); }
    ~ArrayOfString() { destroy(); }

    char** getArray() { return m_array; }
    int size() { return m_size; }

private:
    void setVector(const std::vector<std::string>& vec) {
        m_size = vec.size();
        m_array = new char*[m_size];
        for (int i=0; i<m_size; i++) {
            const std::string& s = vec[i];
            m_array[i] = new char[s.size()+1];
            strcpy(m_array[i], s.c_str());
        }
    }
    void destroy() {
        if (m_array) {
            for (int i=0; i<m_size; i++) delete [] m_array[i];
            delete [] m_array;
            m_array = 0;
        }
    }

    char** m_array = 0;
    int m_size = 0;
};

inline void ShowHelpTip(const char* desc) {
    ImGui::SameLine();
    ImGui::TextDisabled("[?]");
    if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip(desc);
    }
}

inline ImVec2 toImVec2(const tt::Vec2i& v) {
    return ImVec2(v[0], v[1]);
}

#endif  // imgui_util_h
