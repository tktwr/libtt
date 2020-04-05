#pragma once

#include <Eigen/Core>
#include <Eigen/Geometry>
#include <Eigen/Dense>
#include <tt/ext/eigen/eigen_util.h>

namespace tt {
namespace gfx {

using Vec2f = Eigen::Vector2f;
using Vec3f = Eigen::Vector3f;
using Vec4f = Eigen::Vector4f;

using Vec2i = Eigen::Vector2i;
using Vec3i = Eigen::Vector3i;
using Vec4i = Eigen::Vector4i;

inline float length(const Vec3f& v) { return v.norm(); }
inline float distance(const Vec3f& v0, const Vec3f& v1) { return (v0 - v1).norm(); }
inline float dot(const Vec3f& v0, const Vec3f& v1) { return v0.dot(v1); }
inline Vec3f cross(const Vec3f& v0, const Vec3f& v1) { return v0.cross(v1); }
inline Vec3f normalize(const Vec3f& v) { return v.normalized(); }

}
}

