#include "gl_texture.h"

void GLTexture2D::setImage(const tt::Image4uc& image) {
    int w = image.w();
    int h = image.h();
    const uchar* data = reinterpret_cast<const uchar*>(image.data());
    setImage(w, h, data);
}

void GLTexture2D::setImage(GLsizei w, GLsizei h, const GLvoid* data) {
    if (!m_id) {
        glGenTextures(1, &m_id);
    }
    glBindTexture(GL_TEXTURE_2D, m_id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
}

void GLTexture2D::release() {
    if (m_id) {
        glDeleteTextures(1, &m_id);
        m_id = 0;
    }
}

void GLTexture2D::bind() {
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void GLTexture2D::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

