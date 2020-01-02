#include "TreeGenerator.h"

TreeGenerator::TreeGenerator(glm::vec3 position) {
	std::vector<glm::vec3> cubePositions = {
		//  Logs
		glm::vec3(position.x, position.y + 0, position.z), 
		glm::vec3(position.x, position.y + 1, position.z),
		glm::vec3(position.x, position.y + 2, position.z),
		glm::vec3(position.x, position.y + 3, position.z),

		//  Leaves
		glm::vec3(position.x, position.y + 4, position.z),
		glm::vec3(position.x, position.y + 5, position.z),

		glm::vec3(position.x - 1, position.y + 4, position.z),
		glm::vec3(position.x - 2, position.y + 4, position.z),
		glm::vec3(position.x - 2, position.y + 3, position.z),

		glm::vec3(position.x + 1, position.y + 4, position.z),
		glm::vec3(position.x + 2, position.y + 4, position.z),
		glm::vec3(position.x + 2, position.y + 3, position.z),

		glm::vec3(position.x, position.y + 4, position.z - 1),
		glm::vec3(position.x, position.y + 4, position.z - 2),
		glm::vec3(position.x, position.y + 3, position.z - 2),

		glm::vec3(position.x, position.y + 4, position.z + 1),
		glm::vec3(position.x, position.y + 4, position.z + 2),
		glm::vec3(position.x, position.y + 3, position.z + 2),
	};

	for (GLsizei a = 0; a < cubePositions.size(); a++) {
		cubeVector.emplace_back(new CubeGenerator());

		if (a <= 4) {
			cubeVector[a]->setType(CubeGenerator::BlockType::Log_Block);
			cubeVector[a]->setTexture(Texture::get(LOG_TEXTURE_LOCATION));
			cubeVector[a]->setPosition(cubePositions[a]);
		}

		else {
			cubeVector[a]->setType(CubeGenerator::BlockType::Leaf_Block);
			cubeVector[a]->setTexture(Texture::get(LEAF_TEXTURE_LOCATION));
			cubeVector[a]->setPosition(cubePositions[a]);
		}
	}
}

void TreeGenerator::update() {
	//  ?
}

void TreeGenerator::render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection, const Frustum& frustum) { 
	for (auto& cube : cubeVector) {
		if (frustum.isAABBPartiallyInside(cube->getP0(), cube->getP1())) {
			cube->render(glWindow, viewMatrix, projection);
		}
	}
}
