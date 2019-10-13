#pragma once

#include <queue>
#include <stddef.h>

namespace tt {

class Statistics {
public:
    Statistics() : m_max_size(0) {}
    Statistics(size_t max_size) : m_max_size(max_size) {}

    void resize(size_t max_size) {
        m_data.clear();
        m_max_size = max_size;
    }
    void add(float val) {
        m_data.push_back(val);
        if (m_data.size() > m_max_size) m_data.pop_front();
    }
    float getAverage() const {
        float total = 0;
        std::deque<float>::const_iterator i = m_data.begin();
        for (; i != m_data.end(); i++) total += *i;
        return total/m_data.size();
    }

private:
    std::deque<float> m_data;
    size_t m_max_size;
};

}

