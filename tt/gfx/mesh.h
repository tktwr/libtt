#pragma once

#include <memory>
#include <vector>
#include "math.h"
#include "bbox.h"

namespace tt {

struct TriMeshGroup {
	TriMeshGroup() : m_first(0), m_last(0) {}

	int nTriangles() { return m_last - m_first + 1; }

	std::string m_name;
	int m_first, m_last;
};

using TriMeshGroupPtr = std::shared_ptr<TriMeshGroup>;
using TriMeshGroupConstPtr = std::shared_ptr<const TriMeshGroup>;

class TriMesh {
public:
	TriMesh() { m_smooth_angle = 0; }
	virtual ~TriMesh() {}

	void computeBBox();
	BBox getBBox() const { return m_bbox; }

	int nVertices()  const { return m_P.size(); }
	int nNormals()   const { return m_N.size(); }
	int nTexCoords() const { return m_T.size(); }
	int nAmbients()  const { return m_A.size(); }

	int nTriangles() const { return m_idxP.size(); }
	int nGroups()    const { return m_groups.size(); }
	int nMaterials() const { return m_groups.size(); }

	// per vertex methods
	const gfx::Vec3f& P(int tid, int n) const { return m_P[m_idxP[tid][n]]; }
	const gfx::Vec3f& N(int tid, int n) const { return m_N[m_idxN[tid][n]]; }
          gfx::Vec3f& N(int tid, int n)       { return m_N[m_idxN[tid][n]]; }
	const gfx::Vec2f& T(int tid, int n) const { return m_T[m_idxT[tid][n]]; }
	const gfx::Vec4f& A(int tid, int n) const { return m_A[m_idxP[tid][n]]; }

	// per triangle methods
    gfx::Vec3f fN(int tid) const;
	int getGroupID(int tid) const;
	const std::string& getMaterialName(int tid) const;

	// per group methods
	TriMeshGroupPtr getGroup(int i) const { return m_groups[i]; }
	void addGroup(TriMeshGroupPtr grp) { m_groups.push_back(grp); }
	void clearGroups() { m_groups.clear(); }


	BBox m_bbox;

    std::vector<gfx::Vec3f> m_P;
    std::vector<gfx::Vec3f> m_N;
    std::vector<gfx::Vec2f> m_T;
    std::vector<gfx::Vec4f> m_A;

    std::vector<gfx::Vec3i> m_idxP;
    std::vector<gfx::Vec3i> m_idxN;
    std::vector<gfx::Vec3i> m_idxT;

	float m_smooth_angle;

private:
    std::vector<TriMeshGroupPtr> m_groups;
};

void f_mesh_flat_normals(TriMesh* mesh);
void f_mesh_finalize(TriMesh* mesh);

}

