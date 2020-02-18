#include "gl_frame_display.h"
#include <tt/ext/glm/glm_util.h>

static const std::string s_vshader = R"#(
layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 nml;
layout(location = 2) in vec2 uv;
layout(location = 3) in vec4 col;
out vec4 v_color;
out vec2 v_uv;
uniform mat4 transform;

void main() {
    v_color = col;
    v_uv = uv;
    gl_Position = transform * vec4(pos, 1.0);
}
)#";

static const std::string s_fshader = R"#(
in vec4 v_color;
in vec2 v_uv;
out vec4 f_color;
uniform sampler2D tex;

void main() {
    //f_color = vec4(1.0, 0.0, 0.0, 1.0);
    //f_color = vec4(v_color.rgb, 1.0);
    f_color = texture2D(tex, v_uv);
}
)#";

void GLFrameDisplay::setImage(const tt::Image4uc& image) {
    m_image_size[0] = image.w();
    m_image_size[1] = image.h();
    m_tex.setImage(image);
}

void GLFrameDisplay::init() {
    m_prog.setVertexShader(GLProgram::glsl_header + s_vshader);
    m_prog.setFragmentShader(GLProgram::glsl_header + s_fshader);
    m_prog.link();

    m_vao.init();
}

void GLFrameDisplay::draw() {
    glViewport(0, 0, m_screen_size[0], m_screen_size[1]);
    glClearColor4f(m_clear_color.data());
    glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 mat = f_make_scale_mat(toGlmVec2(m_image_size), toGlmVec2(m_screen_size), m_scale, m_fit);

    m_prog.bind();
    m_prog.setUniformMatrix4("transform", &(mat[0][0]));
    m_tex.bind();
    m_prog.setUniform("tex", 0);

    m_vao.draw();

    m_tex.unbind();
    m_prog.unbind();
}

