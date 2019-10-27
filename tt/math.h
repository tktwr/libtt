#pragma once

#include <cmath>

inline double ToRadian(double degree) {
    return degree * M_PI / 180.0;
}

inline double ToDegree(double radian) {
    return radian * 180.0 / M_PI;
}

inline void f_print_mat3_row(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f\n", m[0], m[1], m[2]);
    printf("%f %f %f\n", m[3], m[4], m[5]);
    printf("%f %f %f\n", m[6], m[7], m[8]);
}

inline void f_print_mat3_col(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f\n", m[0], m[3], m[6]);
    printf("%f %f %f\n", m[1], m[4], m[7]);
    printf("%f %f %f\n", m[2], m[5], m[8]);
}

inline void f_print_mat4_row(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f %f\n", m[0],  m[1],  m[2],  m[3]);
    printf("%f %f %f %f\n", m[4],  m[5],  m[6],  m[7]);
    printf("%f %f %f %f\n", m[8],  m[9],  m[10], m[11]);
    printf("%f %f %f %f\n", m[12], m[13], m[14], m[15]);
}

inline void f_print_mat4_col(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f %f\n", m[0], m[4], m[8],  m[12]);
    printf("%f %f %f %f\n", m[1], m[5], m[9],  m[13]);
    printf("%f %f %f %f\n", m[2], m[6], m[10], m[14]);
    printf("%f %f %f %f\n", m[3], m[7], m[11], m[15]);
}

inline void f_print_vec3(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f\n", m[0],  m[1],  m[2]);
}

inline void f_print_vec4(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f %f\n", m[0],  m[1],  m[2],  m[3]);
}

