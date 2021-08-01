#pragma once

#include "gl_vao.h"

class GLVAOQuad : public GLVAO {
public:
    GLVAOQuad() {}
    virtual ~GLVAOQuad() {}

    void init();
    void draw();

    void setQuad();

private:
};

