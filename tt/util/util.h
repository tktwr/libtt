#pragma once

#include <string>

namespace tt {

inline float BytesToKB(std::size_t bytes) {
    return bytes / 1024.f;
}

inline float BytesToMB(std::size_t bytes) {
    return bytes / 1024.f / 1024.f;
}

inline float BytesToGB(std::size_t bytes) {
    return bytes / 1024.f / 1024.f / 1024.f;
}

inline void f_replace(std::string& str, const std::string& src, const std::string& dst) {
    auto pos = str.find(src);
    auto len = src.length();
    if (pos != std::string::npos) {
        str.replace(pos, len, dst);
    }
}

}

