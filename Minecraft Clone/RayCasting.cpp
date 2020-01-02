#include "RayCasting.h"

RayCasting::RayCasting(GLWindow& glWindow, Camera& cam, glm::mat4 projection)
	: glWindow(glWindow)
	, camera(cam)
	, projectionMatrix(projection) {

	viewMatrix = camera.calculateViewMatrix();
}

void RayCasting::update() {
	viewMatrix = camera.calculateViewMatrix();
	currentRay = calculateMouseRay();
}

glm::vec3 RayCasting::calculateMouseRay() {
	GLfloat mouseX = glWindow.getMousePosition().x;
	GLfloat mouseY = glWindow.getMousePosition().y;

	glm::vec2 normalizedcoords = getNormalizedDeviceCoordinates(mouseX, mouseY);
	glm::vec4 clipCoords = glm::vec4(normalizedcoords.x, normalizedcoords.y, -1.f, 1.f);
	glm::vec4 eyeCoords = toEyeCoords(clipCoords);
	glm::vec3 worldRay = toWorldCoords(eyeCoords);

	return worldRay;
}

glm::vec3 RayCasting::toWorldCoords(glm::vec4 eyeCoords) {
	glm::mat4 invertedView = glm::inverse(viewMatrix); 
	glm::vec4 rayWorld = invertedView * eyeCoords; // CHECK (Matrix4f.transform->invertedView, clipCoords)
	glm::vec3 mouseRay = glm::vec3(rayWorld.x, rayWorld.y, rayWorld.z);
	glm::normalize(mouseRay);

	return mouseRay;
}

glm::vec4 RayCasting::toEyeCoords(glm::vec4 clipCoords) {
	glm::mat4 invertedProjection = glm::inverse(projectionMatrix);  // CHECK (Matrix4f.transform->invertedProjection, clipCoords)
	glm::vec4 eyeCoords = invertedProjection * clipCoords;

	return glm::vec4(eyeCoords.x, eyeCoords.y, -1.f, 0.f);
}

glm::vec2 RayCasting::getNormalizedDeviceCoordinates(GLfloat mouseX, GLfloat mouseY) {
	GLfloat x = (2.f * mouseX) / glWindow.getBufferWidth() - 1.f;
	GLfloat y = (2.f * mouseX) / glWindow.getBufferHeight() - 1.f;

	return glm::vec2(x, y);
}
