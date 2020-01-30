#pragma once

namespace tt {

class TriMesh;

class TriMeshInfo {
public:
	int vtx_size;
	int tex_size;
	int nml_size;
	int amb_size;
	int fce_size;
	int tri_size;
	int grp_size;
	int mtl_size;

	TriMeshInfo() {
		vtx_size = 0;
		tex_size = 0;
		nml_size = 0;
		amb_size = 0;
		fce_size = 0;
		tri_size = 0;
		grp_size = 0;
		mtl_size = 0;
	}
};

}

