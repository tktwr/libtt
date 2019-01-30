#ifndef gl_vao_h
#define gl_vao_h

#include "gl.h"

class GLVAO {
public:
    GLVAO() {}
    ~GLVAO() {}

    void init();
    void draw();

private:
    GLuint m_vao;
    GLuint m_vbo_pos;
    GLuint m_vbo_color;
    GLuint m_vbo_uv;
    GLuint m_ebo;
};

#endif  // gl_vao_h

