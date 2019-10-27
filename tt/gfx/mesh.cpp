#include "mesh.h"

using namespace std;

namespace tt {

// counter clock-wise order
gfx::Vec3f f_triangle_normal(const gfx::Vec3f& p0, const gfx::Vec3f& p1, const gfx::Vec3f& p2) {
    //return ((p1-p0).cross(p2-p0)).normalized();
    gfx::Vec3f v1 = p1 - p0;
    gfx::Vec3f v2 = p2 - p0;
    gfx::Vec3f c = v1.cross(v2);
    return gfx::Vec3f(0, 0, 0);
}

//=========================================================================

void TriMesh::computeBBox() {
	BBox bbox;
	bbox.min = m_P[0];
	bbox.max = m_P[0];
	int nvtx = this->nVertices();
	for (int i=1; i<nvtx; i++) bbox.add(m_P[i]);
	m_bbox = bbox;
}

gfx::Vec3f TriMesh::fN(int tid) const {
    return f_triangle_normal(P(tid, 0), P(tid, 1), P(tid, 2));
}

int TriMesh::getGroupID(int tid) const {
	TriMeshGroupPtr grp = nullptr;
	int sz = m_groups.size();
	for (int i=0; i<sz; i++) {
		grp = m_groups[i];
		if (tid <= grp->m_last) return i;
	}
	return -1;
}

const std::string& TriMesh::getMaterialName(int tid) const {
	static std::string none = "";
	int gid = getGroupID(tid);
	TriMeshGroupPtr grp = m_groups[gid];
	if (grp) {
		return grp->m_name;
    } else {
		return none;
    }
}

//=========================================================================

void f_mesh_flat_normals(TriMesh* mesh) {
	int i, j;

	int ntri = mesh->nTriangles();

	mesh->m_N.resize(3 * ntri);
	mesh->m_idxN.resize(ntri);

	// set vertex normal
	for (i=0; i<ntri; i++) {
        gfx::Vec3f nml = mesh->fN(i);
		for (j=0; j<3; j++) {
			mesh->m_N[i * 3 + j] = nml;
		}
	}

	// set vertex normal indices
	for (i=0; i<ntri; i++) {
		int x = i * 3;
		mesh->m_idxN[i] = gfx::Vec3i(x, x + 1, x + 2);
	}
}

void f_mesh_finalize(TriMesh* mesh) {
	mesh->computeBBox();

	if (mesh->nNormals() == 0) {
		f_mesh_flat_normals(mesh);
	}

	if (mesh->nGroups() == 0) {
		TriMeshGroupPtr grp = std::make_shared<TriMeshGroup>();
		grp->m_name = "default";
		grp->m_first = 0;
		grp->m_last = mesh->nTriangles() - 1;
		mesh->addGroup(grp);
	}
}

}

