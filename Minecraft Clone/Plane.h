#ifndef PLANE_H
#define PLANE_H

#include "State.h" 
#include "glm/glm.hpp"

struct Plane {
	Plane() = default;
	Plane(glm::vec3 v, float d);

	bool isPointInside(glm::vec3 p) const;
	bool isSpherePartiallyInside(glm::vec3 center, float radius) const;
	bool isAABBPartiallyInside(glm::vec3 p0, glm::vec3 p1) const;

	glm::vec3 normal;
	GLfloat distance; // Negative distance from the origin to the plane
};

#endif 