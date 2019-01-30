#ifndef glm_util_h
#define glm_util_h

inline glm::vec2 toGlmVec2(const tt::Vec2i& v) {
    return glm::vec2(v[0], v[1]);
}

inline glm::mat4 make_mat(glm::vec2 src_size, glm::vec2 dst_size, float scale, bool fit) {
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

#endif  // glm_util_h

