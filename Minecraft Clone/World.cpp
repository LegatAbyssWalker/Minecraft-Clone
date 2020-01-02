#include "World.h"

World::World(GLWindow& glWindow) : glWindow(glWindow) {
	// Chunk generation

	

	/*-------------------------------------------------------------------------------------------------------------------*/
}


void World::update() {
	
}

void World::render(glm::mat4 viewMatrix) {
	// Projection
	glm::mat4 projection = glm::perspective(glm::radians(45.f), (GLfloat)glWindow.getBufferWidth() / glWindow.getBufferHeight(), 0.1f, 100.f);

	
}

glm::mat4 World::getProjectionMatrix() {
	return glm::perspective(glm::radians(45.f), (GLfloat)glWindow.getBufferWidth() / glWindow.getBufferHeight(), 0.1f, 100.f);
}
