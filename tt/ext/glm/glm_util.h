#pragma once

#include <tt/math.h>
#include <tt/util/type.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

inline glm::vec2 toGlmVec2(const tt::Vec2i& v) {
    return glm::vec2(v[0], v[1]);
}

inline glm::mat4 make_mat(glm::vec2 src_size, glm::vec2 dst_size, float& scale, bool fit) {
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

