#include "ForestBiome.h"

#include <iostream>

ForestBiome::ForestBiome(glm::vec3 chunkPos, GLuint treeMaxAmount, GLuint maxPlantAmount)
	: treeAmount(treeMaxAmount), plantAmount(maxPlantAmount), chunkPos(chunkPos) {

	// Cube generation
	createChunk();

	// Tree generation
	createTrees();

	// Plant generation
	createPlants();
}

void ForestBiome::update() {
	deleteBlock();

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Removes blocks if position.xyz < 0
	for (auto& cube : cubeVector) {
		cube->update();

		if (cube->getPosition().x < 0 || cube->getPosition().y < 0 || cube->getPosition().z < 0) {
			cube->setPosition(glm::vec3((GLint)BLOCK_DEATH_LOCATION));
		}
	}

	// Removes plant if plant is in the same position as the tree
	for (auto& plant : plantVector) {
		for (auto& tree : treeVector) {
			if (plant->getPosition() == tree->getPosition()) {
				plant->setPosition(glm::vec3((GLint)BLOCK_DEATH_LOCATION));
			}
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Tree
	for (auto& tree : treeVector) {
		tree->update();
	}

	// Plant
	for (auto& plant : plantVector) {
		plant->update();
	}
}

void ForestBiome::render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection) {
	Frustum frustum(projection * viewMatrix);

	for (auto& cube : cubeVector) {
		if (frustum.isAABBPartiallyInside(cube->getP0(), cube->getP1())) {
			cube->render(glWindow, viewMatrix, projection);
		}
	}

	for (auto& tree : treeVector) {
		tree->render(glWindow, viewMatrix, projection, frustum);
	}

	for (auto& plant : plantVector) {
		if (frustum.isAABBPartiallyInside(plant->getP0(), plant->getP1())) {
			plant->render(glWindow, viewMatrix, projection);
		}
	}
}

void ForestBiome::addBlock(CubeGenerator::BlockType blockType, const char* textureLocation, glm::vec3 position) {
	cubeVector.emplace_back(new CubeGenerator());

	for (GLsizei a = cubeVector.size() - 1; a < cubeVector.size(); a++) {
		cubeVector[a]->setType(blockType);
		cubeVector[a]->setTexture(Texture::get(textureLocation));
		cubeVector[a]->setPosition(position);
	}
}

void ForestBiome::deleteBlock() {
	// Removing unused blocks
	// Cubes
	auto cubeEnd = std::remove_if(cubeVector.begin(), cubeVector.end(), [](std::unique_ptr<CubeGenerator>& cube) {
		return cube->getPosition() == glm::vec3((GLint)BLOCK_DEATH_LOCATION);
	});
	cubeVector.erase(cubeEnd, cubeVector.end());

	// Plants
	auto plantEnd = std::remove_if(plantVector.begin(), plantVector.end(), [](std::unique_ptr<PlantGenerator>& plant) {
		return plant->getPosition() == glm::vec3((GLint)BLOCK_DEATH_LOCATION);
	});
	plantVector.erase(plantEnd, plantVector.end());

	// Trees
	auto treeEnd = std::remove_if(treeVector.begin(), treeVector.end(), [](std::unique_ptr<TreeGenerator>& tree) {
		return tree->getPosition() == glm::vec3((GLint)BLOCK_DEATH_LOCATION);
	});
	treeVector.erase(treeEnd, treeVector.end());
}

void ForestBiome::createChunk() {
	// Cube generation
	int vecNumber = 0;
	noiseGenerator = std::make_unique<NoiseGenerator>(FOREST_BIOME_AMPLITUDE);

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Creating blocks
	// Creates new blocks in a 16 by x by 16 area (x = random height)
	for (GLsizei x = 0; x < CHUNK_SIZE; x++) {
		for (GLsizei z = 0; z < CHUNK_SIZE; z++) {
			for (GLsizei y = 0; y < Y_VALUE; y++) {
				cubeVector.emplace_back(new CubeGenerator());

				if (y == Y_VALUE - 1) { // 29
					GLsizei heightY = noiseGenerator->generateHeight(cubeVector[vecNumber - 1]->getPosition().x, cubeVector[vecNumber - 1]->getPosition().z);

					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Grass_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(GRASS_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y + heightY, (GLint)z + (GLint)chunkPos.z));
				}

				else if (y < Y_VALUE - 1 && y > 24) { // 25 - 28
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Dirt_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				else if (y > 0 && y < 25) { // 1 - 24
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Stone_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(STONE_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				else { // 0
					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Bedrock_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(BEDROCK_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				vecNumber++;
			}
		}
	}

	// Sets dirt to places without dirt
	for (GLsizei x = 0; x < CHUNK_SIZE; x++) {
		for (GLsizei z = 0; z < CHUNK_SIZE; z++) {
			for (GLsizei y = CHUNK_SIZE - 1; y < MAX_HEIGHT; y++) {
				if (y >= CHUNK_SIZE - 1 && y < MAX_HEIGHT) {
					cubeVector.emplace_back(new CubeGenerator());

					cubeVector[vecNumber]->setType(CubeGenerator::BlockType::Dirt_Block);
					cubeVector[vecNumber]->setTexture(Texture::get(DIRT_TEXTURE_LOCATION));
					cubeVector[vecNumber]->setPosition(glm::vec3((GLint)x + (GLint)chunkPos.x, (GLint)y, (GLint)z + (GLint)chunkPos.z));
				}

				vecNumber++;
			}
		}
	}

	/*-------------------------------------------------------------------------------------------------------------------*/
	// Removing blocks
	// Places dirt blocks that are in same position as grass blocks, someplace else
	for (GLsizei a = 0; a < cubeVector.size(); a++) {
		if (cubeVector[a]->getBlockType() == CubeGenerator::BlockType::Grass_Block) {
			for (GLsizei i = 0; i < cubeVector.size(); i++) {
				if ((cubeVector[i]->getBlockType() != CubeGenerator::BlockType::Grass_Block &&
					(cubeVector[i]->getPosition().x == cubeVector[a]->getPosition().x) &&
					(cubeVector[i]->getPosition().y >= cubeVector[a]->getPosition().y) &&
					(cubeVector[i]->getPosition().z == cubeVector[a]->getPosition().z))) {

					cubeVector[i]->setPosition(glm::vec3((GLint)BLOCK_DEATH_LOCATION));
				}
			}
		}
	}
}

void ForestBiome::createTrees() {
	std::array<Random<>, 3> random;

	GLint randomTreeAmount = random[2].getInt(0, treeAmount);

	for (GLsizei a = 0; a < randomTreeAmount; a++) {
		GLint posX = random[0].getInt(chunkPos.x, (CHUNK_SIZE + chunkPos.x) - 1);
		GLint posZ = random[1].getFloat(chunkPos.z, (CHUNK_SIZE + chunkPos.z) - 1); // New number when float
		GLint posY = getYPosition(posX, posZ);

		treeVector.emplace_back(new TreeGenerator(glm::vec3(posX, posY, posZ)));
	}
}

void ForestBiome::createPlants() {
	std::array<Random<>, 3> random;

	GLuint randomPlantAmount = random[2].getInt(0, plantAmount);

	for (GLsizei a = 0; a < randomPlantAmount; a++) {
		GLint posX = random[0].getInt(chunkPos.x, (CHUNK_SIZE + chunkPos.x) - 1);
		GLint posZ = random[1].getFloat(chunkPos.z, (CHUNK_SIZE + chunkPos.z) - 1); // New number when float
		GLint posY = getYPosition(posX, posZ);

		plantVector.emplace_back(new PlantGenerator());
		plantVector[a]->setPosition(glm::vec3(posX, posY, posZ));
		plantVector[a]->setTexture(Texture::get(ROSE_TEXTURE_LOCATION));
		plantVector[a]->setType(PlantGenerator::PlantType::Rose_Plant);
	}
}

GLint ForestBiome::getYPosition(GLint posX, GLint posZ) {
	for (auto& cube : cubeVector) {
		if (posX == cube->getPosition().x && posZ == cube->getPosition().z) {
			if (cube->getBlockType() == CubeGenerator::BlockType::Grass_Block) {
				return (GLint)cube->getPosition().y + 1;
			}
		}
	}
}
