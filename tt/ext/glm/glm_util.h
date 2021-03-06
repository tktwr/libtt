#pragma once

#include <tt/math.h>
#include <tt/util/type.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

namespace tt {

inline glm::vec2 toGlmVec2(const tt::Vec2i& v) {
    return glm::vec2(v[0], v[1]);
}

inline glm::mat4 f_make_scale_mat(glm::vec2 src_size, glm::vec2 dst_size, float& scale, bool fit) {
    if (fit) {
        glm::vec2 scale_size = dst_size / src_size;
        scale = std::min(scale_size[0], scale_size[1]);
    }
    glm::vec2 ssize = src_size * scale;
    glm::vec2 o = dst_size * 0.5f - ssize * 0.5f;

    glm::mat4 mat = glm::ortho<float>(0, dst_size[0], 0, dst_size[1]);
    mat = glm::translate(mat, glm::vec3(o, 0));
    mat = glm::scale(mat, glm::vec3(ssize, 1));
    mat = glm::translate(mat, glm::vec3(0, 1, 0));
    mat = glm::scale(mat, glm::vec3(1, -1, 1));

    return mat;
}

inline void f_print_mat2_row(const std::string& s, const glm::mat2& m) {
    f_print_mat2_row(s, &(m[0][0]));
}

inline void f_print_mat2_col(const std::string& s, const glm::mat2& m) {
    f_print_mat2_col(s, &(m[0][0]));
}

inline void f_print_mat3_row(const std::string& s, const glm::mat3& m) {
    f_print_mat3_row(s, &(m[0][0]));
}

inline void f_print_mat3_col(const std::string& s, const glm::mat3& m) {
    f_print_mat3_col(s, &(m[0][0]));
}

inline void f_print_mat4_row(const std::string& s, const glm::mat4& m) {
    f_print_mat4_row(s, &(m[0][0]));
}

inline void f_print_mat4_col(const std::string& s, const glm::mat4& m) {
    f_print_mat4_col(s, &(m[0][0]));
}

inline void f_print_vec2(const std::string& s, const glm::vec2& v) {
    f_print_vec2(s, &(v[0]));
}

inline void f_print_vec3(const std::string& s, const glm::vec3& v) {
    f_print_vec3(s, &(v[0]));
}

inline void f_print_vec4(const std::string& s, const glm::vec4& v) {
    f_print_vec4(s, &(v[0]));
}

inline void f_print_vec2i(const std::string& s, const glm::ivec2& v) {
    f_print_vec2i(s, &(v[0]));
}

inline void f_print_vec3i(const std::string& s, const glm::ivec3& v) {
    f_print_vec3i(s, &(v[0]));
}

inline void f_print_vec4i(const std::string& s, const glm::ivec4& v) {
    f_print_vec4i(s, &(v[0]));
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec2& v) {
    return os << v[0] << " " << v[1];
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec3& v) {
    return os << v[0] << " " << v[1] << " " << v[2];
}

inline std::ostream& operator<<(std::ostream& os, const glm::vec4& v) {
    return os << v[0] << " " << v[1] << " " << v[2] << " " << v[3];
}

inline std::ostream& operator<<(std::ostream& os, const glm::ivec2& v) {
    return os << v[0] << " " << v[1];
}

inline std::ostream& operator<<(std::ostream& os, const glm::ivec3& v) {
    return os << v[0] << " " << v[1] << " " << v[2];
}

inline std::ostream& operator<<(std::ostream& os, const glm::ivec4& v) {
    return os << v[0] << " " << v[1] << " " << v[2] << " " << v[3];
}

}

