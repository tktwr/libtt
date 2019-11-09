#include "gl_program.h"
#include <tt/util/log.h>

#ifdef __ANDROID__
const std::string GLProgram::glsl_header = R"#(#version 300 es
precision highp float;
)#";
#else
const std::string GLProgram::glsl_header = R"#(#version 420
)#";
#endif

void f_get_shader_log(GLuint shader) {
    GLint result;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);

    if (result == GL_TRUE) {
        tt::Log::I("compiling shader [success]\n");
    } else if (result == GL_FALSE) {
        tt::Log::I("compiling shader [fail]\n");

        GLint log_length;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_length);

        const GLsizei max_length = 1024;
        GLsizei length;
        GLchar log[max_length];
        glGetShaderInfoLog(shader, max_length, &length, log);

        tt::Log::I("ShaderInfoLog:\n");
        tt::Log::I("%s\n", log);
    }
}

void GLProgram::link() {
    const char* vs_str = m_vertex_shader.c_str();
    GLuint vs_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs_id, 1, &vs_str, NULL);
    glCompileShader(vs_id);

    f_get_shader_log(vs_id);

    const char* fs_str = m_fragment_shader.c_str();
    GLuint fs_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs_id, 1, &fs_str, NULL);
    glCompileShader(fs_id);

    f_get_shader_log(fs_id);

    GLuint prg_id = glCreateProgram();
    glAttachShader(prg_id, vs_id);
    glAttachShader(prg_id, fs_id);

    glLinkProgram(prg_id);

    m_prog_id = prg_id;
}

void GLProgram::bind() {
    glUseProgram(m_prog_id);
}

void GLProgram::unbind() {
    glUseProgram(0);
}

void GLProgram::setUniformMatrix4(const std::string& str, const GLfloat* val) {
    GLint loc = glGetUniformLocation(m_prog_id, str.c_str());
    glUniformMatrix4fv(loc, 1, GL_FALSE, val);
}

void GLProgram::setUniform(const std::string& str, GLint val) {
    GLint loc = glGetUniformLocation(m_prog_id, str.c_str());
    glUniform1i(loc, val);
}

void GLProgram::setUniform(const std::string& str, GLfloat val) {
    GLint loc = glGetUniformLocation(m_prog_id, str.c_str());
    glUniform1f(loc, val);
}

