#ifndef gl_texture_h
#define gl_texture_h

#include "gl.h"
#include <tt/gfx/image.h>

class GLTexture2D {
public:
    GLTexture2D() {}
    ~GLTexture2D() { release(); }

    int w() const { return m_w; }
    int h() const { return m_h; }
    GLuint id() const { return m_id; }
    void setImage(const tt::Image4uc& image);
    void setImage(GLsizei w, GLsizei h, const GLvoid* data);
    void release();
    void bind();
    void unbind();

private:
    int m_w = 0;
    int m_h = 0;
    GLuint m_id = 0;
};

#endif  // gl_texture_h
