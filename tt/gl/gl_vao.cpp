#include "gl_vao.h"
#include <vector>
#include <tt/gfx/math.h>
#include <tt/util/log.h>

void GLVAO::init() {
}

void GLVAO::setPos(size_t size, float* data) {
    m_pos_size = size;
    m_pos_data = data;
}

void GLVAO::setNml(size_t size, float* data) {
    m_nml_size = size;
    m_nml_data = data;
}

void GLVAO::setUv(size_t size, float* data) {
    m_uv_size = size;
    m_uv_data = data;
}

void GLVAO::setCol(size_t size, float* data) {
    m_col_size = size;
    m_col_data = data;
}

void GLVAO::setIdx(size_t size, int* data) {
    m_idx_size = size;
    m_idx_data = data;
}

void GLVAO::setVBO() {
    unsetVBO();

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo_pos);
    glGenBuffers(1, &m_vbo_nml);
    glGenBuffers(1, &m_vbo_uv);
    glGenBuffers(1, &m_vbo_col);
    glGenBuffers(1, &m_ebo);

    tt::Log::I("m_vao=%d\n", m_vao);
    tt::Log::I("m_vbo_pos=%d\n", m_vbo_pos);
    tt::Log::I("m_vbo_nml=%d\n", m_vbo_nml);
    tt::Log::I("m_vbo_uv=%d\n", m_vbo_uv);
    tt::Log::I("m_vbo_col=%d\n", m_vbo_col);
    tt::Log::I("m_ebo=%d\n", m_ebo);

    glBindVertexArray(m_vao);

    if (m_vbo_pos) {
        // Position attribute
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_pos);
        glBufferData(GL_ARRAY_BUFFER, m_pos_size, m_pos_data, GL_STATIC_DRAW);
        GLint loc_pos = 0;
        glEnableVertexAttribArray(loc_pos);
        glVertexAttribPointer(loc_pos, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    }

    if (m_vbo_nml) {
        // Normal attribute
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_nml);
        glBufferData(GL_ARRAY_BUFFER, m_nml_size, m_nml_data, GL_STATIC_DRAW);
        GLint loc_nml = 1;
        glEnableVertexAttribArray(loc_nml);
        glVertexAttribPointer(loc_nml, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    }

    if (m_vbo_uv) {
        // UV attribute
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uv);
        glBufferData(GL_ARRAY_BUFFER, m_uv_size, m_uv_data, GL_STATIC_DRAW);
        GLint loc_uv = 2;
        glEnableVertexAttribArray(loc_uv);
        glVertexAttribPointer(loc_uv, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    }

    if (m_vbo_col) {
        // Color attribute
        glBindBuffer(GL_ARRAY_BUFFER, m_vbo_col);
        glBufferData(GL_ARRAY_BUFFER, m_col_size, m_col_data, GL_STATIC_DRAW);
        GLint loc_col = 3;
        glEnableVertexAttribArray(loc_col);
        glVertexAttribPointer(loc_col, 4, GL_FLOAT, GL_FALSE, 0, (GLvoid*)0);
    }

    // Element Array Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_idx_size, m_idx_data, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLVAO::unsetVBO() {
    if (m_vbo_pos) {
        glDeleteBuffers(1, &m_vbo_pos);
        m_vbo_pos = 0;
    }
    if (m_vbo_nml) {
        glDeleteBuffers(1, &m_vbo_nml);
        m_vbo_nml = 0;
    }
    if (m_vbo_uv) {
        glDeleteBuffers(1, &m_vbo_uv);
        m_vbo_uv = 0;
    }
    if (m_vbo_col) {
        glDeleteBuffers(1, &m_vbo_col);
        m_vbo_col = 0;
    }
    if (m_ebo) {
        glDeleteBuffers(1, &m_ebo);
        m_ebo = 0;
    }
    if (m_vao) {
        glDeleteVertexArrays(1, &m_vao);
        m_vao = 0;
    }
}

void GLVAO::unsetData() {
    m_pos_size = 0;
    m_pos_data = 0;

    m_nml_size = 0;
    m_nml_data = 0;

    m_uv_size = 0;
    m_uv_data = 0;

    m_col_size = 0;
    m_col_data = 0;

    m_idx_size = 0;
    m_idx_data = 0;
}

void GLVAO::draw() {
    if (!m_vao) return;

    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, m_idx_size / sizeof(int), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

