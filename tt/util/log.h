#ifndef tt_log_h
#define tt_log_h

#include <stdarg.h>
#include <stdio.h>

namespace tt {

class Log {
public:
    Log() {}

    static void I(const char* fmt, ...) {
        char buf[buf_size];
        va_list args;

        va_start(args, fmt);
        vsnprintf(buf, buf_size, fmt, args);
        buf[buf_size-1] = 0;
        va_end(args);

        fprintf(stdout, "[I] %s", buf);
        fflush(stdout);
    }

    static void E(const char* fmt, ...) {
        char buf[buf_size];
        va_list args;

        va_start(args, fmt);
        vsnprintf(buf, buf_size, fmt, args);
        buf[buf_size-1] = 0;
        va_end(args);

        fprintf(stdout, "[E] %s", buf);
        fflush(stdout);
    }

private:
    static const int buf_size = 1024;
};

}

#endif  // tt_log_h

