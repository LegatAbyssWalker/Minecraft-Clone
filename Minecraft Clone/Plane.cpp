#include "Plane.h"

Plane::Plane(glm::vec3 v, float d) : normal(v), distance(d) {
	auto length = glm::length(v);
	normal /= length;
	distance /= length;
}

bool Plane::isPointInside(glm::vec3 p) const { 
    return glm::dot(p, normal) + distance >= 0;
}

bool Plane::isSpherePartiallyInside(glm::vec3 center, float radius) const {
    return glm::dot(center, normal) + distance >= -radius;
}

bool Plane::isAABBPartiallyInside(glm::vec3 p0, glm::vec3 p1) const { 
	glm::vec3 points[8] = {
		glm::vec3(p0.x, p0.y, p0.z),
		glm::vec3(p0.x, p0.y, p1.z),
		glm::vec3(p0.x, p1.y, p0.z),
		glm::vec3(p0.x, p1.y, p1.z),
		glm::vec3(p1.x, p0.y, p0.z),
		glm::vec3(p1.x, p0.y, p1.z),
		glm::vec3(p1.x, p1.y, p0.z),
		glm::vec3(p1.x, p1.y, p1.z),
	};

	for (glm::vec3 p : points) {
		if (isPointInside(p)) {
			return true;
		}
	}

	return false;
}