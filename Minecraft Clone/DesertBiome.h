#ifndef DESERTBIOME_H
#define DESERTBIOME_H

#include "Biome.h"
#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "NoiseGenerator.h"
#include "CactusGenerator.h"
#include "Random.h"
#include "PlantGenerator.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class DesertBiome : public Biome {
	public:
		DesertBiome() = default;
		DesertBiome(glm::vec3 chunkPos, GLuint shrubMaxAmount, GLuint cactusMaxAmount);

		void update();
		void render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection);

		void addBlock(CubeGenerator::BlockType blockType, const char* textureLocation, glm::vec3 position);
		void deleteBlock();

		void createChunk();
		void createCactus();
		void createShrubs();
		void replaceBlocks();

		GLuint getBlockAmount() const { return cubeVector.size(); }
		GLint getYPosition(GLint posX, GLint posZ);


	private:
		GLuint shrubAmount, cactusAmount;
		glm::vec3 chunkPos;

		std::unique_ptr<NoiseGenerator> noiseGenerator = nullptr;
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
		std::vector<std::unique_ptr<PlantGenerator>> plantVector;
		std::vector<std::unique_ptr<CactusGenerator>> cactusVector;
};

#endif