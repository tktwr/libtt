#pragma once

#include "gl_vao.h"
#include <tt/gfx/mesh.h>

class GLVAOMesh : public GLVAO {
public:
    GLVAOMesh() {}
    virtual ~GLVAOMesh() {}

    void init();
    void draw();

    void setMesh(const tt::TriMesh* mesh);

private:
};
