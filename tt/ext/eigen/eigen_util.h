#pragma once

#include <tt/math.h>
#include <Eigen/Core>

namespace tt {

inline void f_print_mat2_row(const std::string& s, const Eigen::Matrix2f& m) {
    f_print_mat2_row(s, m.data());
}

inline void f_print_mat2_col(const std::string& s, const Eigen::Matrix2f& m) {
    f_print_mat2_col(s, m.data());
}

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

inline void f_print_vec2(const std::string& s, const Eigen::Vector2f& v) {
    f_print_vec2(s, v.data());
}

inline void f_print_vec3(const std::string& s, const Eigen::Vector3f& v) {
    f_print_vec3(s, v.data());
}

inline void f_print_vec4(const std::string& s, const Eigen::Vector4f& v) {
    f_print_vec4(s, v.data());
}

inline void f_print_vec2i(const std::string& s, const Eigen::Vector2i& v) {
    f_print_vec2i(s, v.data());
}

inline void f_print_vec3i(const std::string& s, const Eigen::Vector3i& v) {
    f_print_vec3i(s, v.data());
}

inline void f_print_vec4i(const std::string& s, const Eigen::Vector4i& v) {
    f_print_vec4i(s, v.data());
}

}

