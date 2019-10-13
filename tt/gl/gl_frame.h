#pragma once

#include "gl.h"
#include "gl_program.h"
#include "gl_vao.h"
#include "gl_fbo.h"

class GLFrame {
public:
    GLFrame() {}
    virtual ~GLFrame() {}

    virtual void init() {}
    virtual void draw() {}

    void drawToFBO();

    GLuint getColorTexId() const { return m_fbo.getColorTexId(); }
    GLuint getDepthTexId() const { return m_fbo.getDepthTexId(); }

    void setScreenSize(int w, int h);
    const tt::Vec2i& getScreenSize() const { return m_screen_size; }

protected:
    GLProgram m_prog;
    GLVAO m_vao;
    GLFBO m_fbo;

    tt::Color4f m_clear_color = {0.2f, 0.2f, 0.2f, 1.0f};
    tt::Vec2i m_screen_size = {0, 0};
};

