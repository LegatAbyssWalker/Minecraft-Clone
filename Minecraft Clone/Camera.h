#ifndef CAMERA_H
#define CAMERA_H

#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GLFW/glfw3.h"

#include <iostream>

class Camera {
	public:
		Camera(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f), glm::vec3 up = glm::vec3(0.f, 1.f, 0.f), 
			GLfloat yaw = -90.f, GLfloat pitch = 0.f, GLfloat movementSpeed = 2.5f, GLfloat mouseSensitivity = 0.3f);

		void processKeyboard(bool* keys, GLfloat deltaTime);
		void processMouseMovement(GLfloat xChange, GLfloat yChange);

		const glm::vec3 getPosition() { return position; }
		glm::mat4 calculateViewMatrix() { return glm::lookAt(position, position + front, up); };

	private:
		glm::vec3 position;
		glm::vec3 up;
		glm::vec3 front;
		glm::vec3 right;
		glm::vec3 worldUp;

		GLfloat yaw; // Left and right (X-Axis)
		GLfloat pitch; // Up and down (Y-Axis)

		GLfloat movementSpeed;
		GLfloat mouseSensitivity;

		void updateCameraVectors();
};

#endif