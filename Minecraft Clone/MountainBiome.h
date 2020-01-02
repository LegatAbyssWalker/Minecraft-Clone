#ifndef MOUNTAINBIOME_H
#define MOUNTAINBIOME_H

#include "Biome.h"
#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "NoiseGenerator.h"
#include "Random.h"
#include "PlantGenerator.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class MountainBiome : public Biome {
	public:
		MountainBiome() = default;
		MountainBiome(glm::vec3 chunkPos, GLuint maxPlantAmount);

		void update();
		void render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection);

		void addBlock(CubeGenerator::BlockType blockType, const char* textureLocation, glm::vec3 position);
		void deleteBlock();

		void createChunk();
		void createPlants();
		void replaceBlocks();

		GLuint getBlockAmount() const { return cubeVector.size(); }
		GLint getYPosition(GLint posX, GLint posZ);


	private:
		GLuint plantAmount;
		glm::vec3 chunkPos;

		std::unique_ptr<NoiseGenerator> noiseGenerator = nullptr;
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
		std::vector<std::unique_ptr<PlantGenerator>> plantVector;
};

#endif