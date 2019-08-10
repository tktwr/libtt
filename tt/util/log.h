#pragma once

namespace tt {

class Log {
public:
    static void I(const char* fmt, ...);
    static void E(const char* fmt, ...);
};

}

