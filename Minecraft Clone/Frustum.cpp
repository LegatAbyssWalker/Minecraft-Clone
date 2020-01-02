#include "Frustum.h"

#include <algorithm>


Frustum::Frustum(glm::mat4 modelProjection) {
	// Convenience
	const glm::mat4& m = modelProjection;

	// Planes extraction algorithm 
	// http://www.lighthouse3d.com/tutorials/view-frustum-culling/clip-space-approach-extracting-the-planes/
	for (GLint i = 0; i < 3; i++) {
		planes[2 * i] = Plane(glm::vec3(m[0][3] + m[0][i], m[1][3] + m[1][i], m[2][3] + m[2][i]), m[3][3] + m[3][i]);
		planes[2 * i + 1] = Plane(glm::vec3(m[0][3] - m[0][i], m[1][3] - m[1][i], m[2][3] - m[2][i]), m[3][3] - m[3][i]);
	}


} 

bool Frustum::isPointInside(glm::vec3 p) const {
	for (const Plane& plane : planes) {
		if (!plane.isPointInside(p)) { 
			return false;
		}
	}

	return true; 
} 

bool Frustum::isSpherePartiallyInside(glm::vec3 center, float radius) const {
	for (const Plane& plane : planes) {
		if (!plane.isSpherePartiallyInside(center, radius)) {
			return false;
		}
	}

	return true;
}

bool Frustum::isAABBPartiallyInside(glm::vec3 p0, glm::vec3 p1) const {
	for (const auto& plane : planes) {
		if (!plane.isAABBPartiallyInside(p0, p1)) {
			return false;
		}
	}

	return true;
}
