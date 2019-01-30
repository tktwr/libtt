#ifndef gl_program_h
#define gl_program_h

#include "gl.h"

class GLProgram {
public:
    GLProgram() {}
    ~GLProgram() {}

    void setVertexShader(const std::string& shader) { m_vertex_shader = shader; }
    void setFragmentShader(const std::string& shader) { m_fragment_shader = shader; }
    void link();

    void bind();
    void unbind();

    void setUniformMatrix4(const std::string& str, const GLfloat* val);
    void setUniform(const std::string& str, GLint val);
    void setUniform(const std::string& str, GLfloat val);

private:
    GLuint m_prog_id = 0;
    std::string m_vertex_shader;
    std::string m_fragment_shader;
};

#endif  // gl_program_h

