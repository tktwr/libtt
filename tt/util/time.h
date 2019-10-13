#pragma once

#include <chrono>
#include <string>
#include <map>

namespace tt {

class Time {
public:
    Time() {}

    void start() { m_start = std::chrono::system_clock::now(); }
    void end() { m_end = std::chrono::system_clock::now(); }

    void setMessage(const std::string& msg) { m_message = msg; }
    std::string getMessage() const { return m_message; }

    float getElapsedMSec() const {
        return static_cast<float>(std::chrono::duration_cast<std::chrono::milliseconds>(m_end-m_start).count());
    }

private:
    std::chrono::system_clock::time_point m_start, m_end;
    std::string m_message;
};

class TimeCollection {
public:
    Time& operator[](const std::string& key) { return m_collect[key]; }

private:
    std::map<std::string, Time> m_collect;
};

}

