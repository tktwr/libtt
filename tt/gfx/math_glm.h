#pragma once

#include <glm/glm.hpp>
#include <tt/ext/glm/glm_util.h>

namespace tt {
namespace gfx {

using Vec2f = glm::vec2;
using Vec3f = glm::vec3;
using Vec4f = glm::vec4;

using Vec2i = glm::ivec2;
using Vec3i = glm::ivec3;
using Vec4i = glm::ivec4;

inline float length(const Vec3f& v) { return glm::length(v); }
inline float distance(const Vec3f& v0, const Vec3f& v1) { return glm::distance(v0, v1); }
inline float dot(const Vec3f& v0, const Vec3f& v1) { return glm::dot(v0, v1); }
inline Vec3f cross(const Vec3f& v0, const Vec3f& v1) { return glm::cross(v0, v1); }
inline Vec3f normalize(const Vec3f& v) { return glm::normalize(v); }

}
}

