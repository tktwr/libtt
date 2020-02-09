#include "gl_vao_mesh.h"
#include <tt/gfx/mesh.h>

void GLVAOMesh::init() {
}

void GLVAOMesh::draw() {
    GLVAO::draw();
}

void GLVAOMesh::setMesh(const tt::TriMesh* mesh) {
    setPos(sizeof(tt::gfx::Vec3f) * mesh->nVertices(),  (float*)(mesh->m_P.data()));
    setNml(sizeof(tt::gfx::Vec3f) * mesh->nNormals(),   (float*)(mesh->m_N.data()));
    setUv (sizeof(tt::gfx::Vec2f) * mesh->nTexCoords(), (float*)(mesh->m_T.data()));
    setIdx(sizeof(int) * 3 * mesh->nTriangles(), (int*)(mesh->m_idxP.data()));
    setVBO();
}

