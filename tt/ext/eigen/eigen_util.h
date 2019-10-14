#pragma once

#include <tt/math.h>
#include <Eigen/Core>
#include <cstdio>
#include <iostream>

inline void f_print_mat3_row(const std::string& s, const Eigen::Matrix3f& m) {
    f_print_mat3_row(s, m.data());
}

inline void f_print_mat3_col(const std::string& s, const Eigen::Matrix3f& m) {
    f_print_mat3_col(s, m.data());
}

inline void f_print_mat4_row(const std::string& s, const Eigen::Matrix4f& m) {
    f_print_mat4_row(s, m.data());
}

inline void f_print_mat4_col(const std::string& s, const Eigen::Matrix4f& m) {
    f_print_mat4_col(s, m.data());
}

