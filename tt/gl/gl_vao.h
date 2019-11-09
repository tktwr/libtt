#pragma once

#include "gl.h"

class GLVAO {
public:
    GLVAO() {}
    virtual ~GLVAO() {}

    void init();
    void draw();

    void setPos(size_t size, float* data);
    void setNml(size_t size, float* data);
    void setUv (size_t size, float* data);
    void setCol(size_t size, float* data);
    void setIdx(size_t size, int* data);
    void setVBO();

private:
    GLuint m_vao = 0;
    GLuint m_vbo_pos = 0;
    GLuint m_vbo_nml = 0;
    GLuint m_vbo_uv = 0;
    GLuint m_vbo_col = 0;
    GLuint m_ebo = 0;

    size_t m_pos_size = 0;
    float* m_pos_data = 0;

    size_t m_nml_size = 0;
    float* m_nml_data = 0;

    size_t m_uv_size = 0;
    float* m_uv_data = 0;

    size_t m_col_size = 0;
    float* m_col_data = 0;

    size_t m_idx_size = 0;
    int*   m_idx_data = 0;
};

