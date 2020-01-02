#include "CactusGenerator.h"

CactusGenerator::CactusGenerator(glm::vec3 position) {
	std::vector<glm::vec3> cubePositions = {
		// Cactus 1
		glm::vec3(position.x, position.y + 0, position.z),
		glm::vec3(position.x, position.y + 1, position.z),
		glm::vec3(position.x, position.y + 2, position.z)
	};

	for (GLsizei a = 0; a < cubePositions.size(); a++) {
		cubeVector.emplace_back(new CubeGenerator());
		cubeVector[a]->setType(CubeGenerator::BlockType::Cactus_Block);
		cubeVector[a]->setTexture(Texture::get(CACTUS_TEXTURE_LOCATION));
		cubeVector[a]->setPosition(cubePositions[a]);
	}
}

void CactusGenerator::update() {
	// ? 
}

void CactusGenerator::render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection, const Frustum& frustum) {
	for (auto& cube : cubeVector) {
		if (frustum.isAABBPartiallyInside(cube->getP0(), cube->getP1())) {
			cube->render(glWindow, viewMatrix, projection);
		}
	}
}
