#include "gl_vao_quad.h"
#include <tt/gfx/math.h>
#include <vector>

void GLVAOQuad::init() {
    setQuad();
}

void GLVAOQuad::draw() {
    GLVAO::draw();
}

void GLVAOQuad::setQuad() {
    std::vector<tt::gfx::Vec3f> m_pos;
    std::vector<tt::gfx::Vec3f> m_nml;
    std::vector<tt::gfx::Vec2f> m_uv;
    std::vector<tt::gfx::Vec4f> m_col;
    std::vector<int> m_idx;

    m_pos = {
        {0.0f, 0.0f, 0.0f},
        {1.0f, 0.0f, 0.0f},
        {1.0f, 1.0f, 0.0f},
        {0.0f, 1.0f, 0.0f}
    };
    m_nml = {
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f},
        {0.0f, 0.0f, 1.0f}
    };
    m_uv = {
        {0.0f, 0.0f},
        {1.0f, 0.0f},
        {1.0f, 1.0f},
        {0.0f, 1.0f}
    };
    m_col = {
        {0.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 0.0f, 0.0f, 1.0f},
        {1.0f, 1.0f, 0.0f, 1.0f},
        {0.0f, 1.0f, 0.0f, 1.0f}
    };
    m_idx = {0, 1, 2, 0, 2, 3};

    setPos(sizeof(tt::gfx::Vec3f) * m_pos.size(), (float*)(m_pos.data()));
    setNml(sizeof(tt::gfx::Vec3f) * m_nml.size(), (float*)(m_nml.data()));
    setUv (sizeof(tt::gfx::Vec2f) * m_uv.size(),  (float*)(m_uv.data()));
    setCol(sizeof(tt::gfx::Vec4f) * m_col.size(), (float*)(m_col.data()));
    setIdx(sizeof(int) * m_idx.size(), (int*)(m_idx.data()));

    setVBO();
}

