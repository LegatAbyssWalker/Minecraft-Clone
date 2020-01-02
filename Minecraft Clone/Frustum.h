#ifndef FRUSTUM_H
#define FRUSTUM_H

#include "State.h"
#include "Plane.h"

constexpr int NUM_PLANES = 6;

class Frustum {
	public:
		Frustum(glm::mat4 modelProjection); 

		bool isPointInside(glm::vec3 p) const;
		bool isSpherePartiallyInside(glm::vec3 center, float radius) const;
		bool isAABBPartiallyInside(glm::vec3 p0, glm::vec3 p1) const;

	private:
		// The six frustum planes
		Plane planes[NUM_PLANES];
};

#endif