#include "log.h"
#include <stdarg.h>

#if __ANDROID__
#include <android/log.h>
#else
#include <stdio.h>
#endif

#define BUF_SIZE 1024

namespace tt {

#if __ANDROID__

void Log::I(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_INFO, "[I]", fmt, args);
    va_end(args);
}

void Log::E(const char* fmt, ...) {
    va_list args;

    va_start(args, fmt);
    __android_log_vprint(ANDROID_LOG_ERROR, "[E]", fmt, args);
    va_end(args);
}

#else

void Log::I(const char* fmt, ...) {
    char buf[BUF_SIZE];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, BUF_SIZE, fmt, args);
    va_end(args);
    buf[BUF_SIZE-1] = 0;

    fprintf(stdout, "[I] %s", buf);
    fflush(stdout);
}

void Log::E(const char* fmt, ...) {
    char buf[BUF_SIZE];
    va_list args;

    va_start(args, fmt);
    vsnprintf(buf, BUF_SIZE, fmt, args);
    va_end(args);
    buf[BUF_SIZE-1] = 0;

    fprintf(stdout, "[E] %s", buf);
    fflush(stdout);
}

#endif

}

