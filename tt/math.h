#pragma once

#include <cmath>
#include <cstdio>
#include <iostream>

#if !defined(M_PI)
#define M_PI		3.14159265358979323846
#endif

namespace tt {

inline double ToRadian(double degree) {
    return degree * M_PI / 180.0;
}

inline double ToDegree(double radian) {
    return radian * 180.0 / M_PI;
}

inline void f_print_mat2_row(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f\n", m[0], m[1]);
    printf("%f %f\n", m[2], m[3]);
}

inline void f_print_mat2_col(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f\n", m[0], m[2]);
    printf("%f %f\n", m[1], m[3]);
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

inline void f_print_vec2(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f\n", m[0], m[1]);
}

inline void f_print_vec3(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f\n", m[0], m[1], m[2]);
}

inline void f_print_vec4(const std::string& s, const float* m) {
    std::cout << s << std::endl;
    printf("%f %f %f %f\n", m[0], m[1], m[2], m[3]);
}

inline void f_print_vec2i(const std::string& s, const int* m) {
    std::cout << s << std::endl;
    printf("%d %d\n", m[0], m[1]);
}

inline void f_print_vec3i(const std::string& s, const int* m) {
    std::cout << s << std::endl;
    printf("%d %d %d\n", m[0], m[1], m[2]);
}

inline void f_print_vec4i(const std::string& s, const int* m) {
    std::cout << s << std::endl;
    printf("%d %d %d %d\n", m[0], m[1], m[2], m[3]);
}

}

