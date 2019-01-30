#include "gl_frame.h"

void GLFrame::setScreenSize(int w, int h) {
    if (m_screen_size != tt::Vec2i{w, h}) {
        m_screen_size[0] = w;
        m_screen_size[1] = h;
        m_fbo.close();
        m_fbo.open(w, h);
    }
}

void GLFrame::drawToFBO() {
    m_fbo.bind();
    draw();
    m_fbo.unbind();
}

