#include "Camera.h"


Camera::Camera(glm::vec3 position, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat movementSpeed, GLfloat sensitivity)
	: position(position), worldUp(up), yaw(yaw), pitch(pitch), movementSpeed(movementSpeed), mouseSensitivity(sensitivity) {


	front = glm::vec3(0.f, 0.f, -1.f);
	updateCameraVectors();
}

void Camera::processKeyboard(bool* keys, GLfloat deltaTime) {
	GLfloat velocity = movementSpeed * deltaTime;
	
	// WASD
	if (keys[GLFW_KEY_W]) { position += front * velocity; }
	if (keys[GLFW_KEY_A]) { position -= right * velocity; }
	if (keys[GLFW_KEY_S]) { position -= front * velocity; }
	if (keys[GLFW_KEY_D]) { position += right * velocity; }

	// SHIFT/SPACE
	if (keys[GLFW_KEY_LEFT_SHIFT]) { position -= up * velocity; }
	if (keys[GLFW_KEY_SPACE])      { position += up * velocity; }

	// W and F
	if (keys[GLFW_KEY_W] && keys[GLFW_KEY_F]) { position += front * (velocity + velocity); }
}

void Camera::processMouseMovement(GLfloat xChange, GLfloat yChange) {
	xChange *= mouseSensitivity;
	yChange *= mouseSensitivity;

	yaw += xChange; 
	pitch += yChange; 

	// Make sure that when the pitch is out of bounds, the screen does not flip
	if (pitch > 89.f) {
		pitch = 89.f;
	}
	if (pitch < -89.f) {
		pitch = -89.f;
	}

	// Update front, right, and up vectors when updating euler angles
	updateCameraVectors();
}

void Camera::updateCameraVectors() {
	glm::vec3 functionFront;

	functionFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	functionFront.y = sin(glm::radians(pitch));
	functionFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	front   = glm::normalize(functionFront);

	right = glm::normalize(glm::cross(front, worldUp));
	up    = glm::normalize(glm::cross(right, front));
}