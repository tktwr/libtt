#pragma once

#include "math.h"
#include "gm.h"

namespace tt {

class BBox {
public:
	BBox() { init(); }
	BBox(float _minx, float _miny, float _minz, float _maxx, float _maxy, float _maxz) {
		min[0] = _minx; min[1] = _miny; min[2] = _minz;
		max[0] = _maxx; max[1] = _maxy; max[2] = _maxz;
	}
	BBox(const float _min[3], const float _max[3]) {
		min[0] = _min[0]; min[1] = _min[1]; min[2] = _min[2];
		max[0] = _max[0]; max[1] = _max[1]; max[2] = _max[2];
	}

	void init() {
		float s = 1e10;
		min[0] = s; min[1] = s; min[2] = s;
		max[0] = -s; max[1] = -s; max[2] = -s;
	}
	void add(const gfx::Vec3f& v) {
		min[0] = gmMin(min[0], v[0]);
		min[1] = gmMin(min[1], v[1]);
		min[2] = gmMin(min[2], v[2]);
		max[0] = gmMax(max[0], v[0]);
		max[1] = gmMax(max[1], v[1]);
		max[2] = gmMax(max[2], v[2]);
	}

    gfx::Vec3f getPoint(int idx) const {
		int x, y, z;
        gfx::Vec3f p = min;
		x = idx    & 0x1;
		y = idx>>1 & 0x1;
		z = idx>>2 & 0x1;
		if (x) p[0] = max[0];
		if (y) p[1] = max[1];
		if (z) p[2] = max[2];
		return p;
	}
    gfx::Vec3f center() const { return .5 * (min + max); }
    gfx::Vec3f size() const { return max - min; }
	float xsize() const { return max[0] - min[0]; }
	float ysize() const { return max[1] - min[1]; }
	float zsize() const { return max[2] - min[2]; }
	float length(int axis) const { return max[axis] - min[axis]; }
	float diameter() const { return (max - min).norm(); }
	int getMaxAxis(float& length) const {
        gfx::Vec3f len = size();
		int axis = gmMaxAxis(len[0], len[1], len[2]);
		length = len[axis];
		return axis;
	}

    gfx::Vec3f min, max;
};

class BBoxi {
public:
    gfx::Vec3i min, max;
};

}

