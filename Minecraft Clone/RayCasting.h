#ifndef RAYCASTING_H
#define RAYCASTING_H

#include "State.h"
#include "Camera.h"
#include "GLWindow.h"

#include <iostream>
#include <algorithm>

class RayCasting {
	public:
		RayCasting(GLWindow& glWindow, Camera& cam, glm::mat4 projection);

		void update();

		glm::vec3 calculateMouseRay();
		glm::vec3 toWorldCoords(glm::vec4 eyeCoords);
		glm::vec4 toEyeCoords(glm::vec4 clipCoords);
		glm::vec2 getNormalizedDeviceCoordinates(GLfloat mouseX, GLfloat mouseY);

		glm::vec3 getCurrentRay() { return currentRay; }

	private:
		Camera& camera;
		GLWindow& glWindow;
		
		glm::vec3 currentRay;
		glm::mat4 projectionMatrix;
		glm::mat4 viewMatrix;
};

#endif