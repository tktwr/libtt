#include "gl_vao.h"

void GLVAO::init() {
    GLfloat vertices[] = {
        0, 0, 0,
        1, 0, 0,
        1, 1, 0,
        0, 1, 0
    };
    GLfloat colors[] = {
        0, 0, 0, 1,
        1, 0, 0, 1,
        1, 1, 0, 1,
        0, 1, 0, 1
    };
    GLfloat uv[] = {
        0, 0,
        1, 0,
        1, 1,
        0, 1
    };
    int indices[] = {0, 1, 2, 0, 2, 3};

    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo_pos);
    glGenBuffers(1, &m_vbo_color);
    glGenBuffers(1, &m_vbo_uv);
    glGenBuffers(1, &m_ebo);

    glBindVertexArray(m_vao);

    // Position attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_pos);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    GLint loc_pos = 0;
    glEnableVertexAttribArray(loc_pos);
    glVertexAttribPointer(loc_pos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

    // Color attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_color);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    GLint loc_color = 1;
    glEnableVertexAttribArray(loc_color);
    glVertexAttribPointer(loc_color, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);

    // UV attribute
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo_uv);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);
    GLint loc_uv = 2;
    glEnableVertexAttribArray(loc_uv);
    glVertexAttribPointer(loc_uv, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)0);

    // Element Array Buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void GLVAO::draw() {
    glBindVertexArray(m_vao);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

