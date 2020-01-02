#ifndef FORESTBIOME_H
#define FORESTBIOME_H

#include "Biome.h"
#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "NoiseGenerator.h"
#include "Random.h"
#include "TreeGenerator.h"
#include "PlantGenerator.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class ForestBiome : public Biome {
	public:
		ForestBiome() = default;
		ForestBiome(glm::vec3 chunkPos, GLuint treeMaxAmount, GLuint maxPlantAmount);

		void update();
		void render(GLWindow & glWindow, glm::mat4 viewMatrix, glm::mat4 projection);

		void addBlock(CubeGenerator::BlockType blockType, const char* textureLocation, glm::vec3 position);
		void deleteBlock();

		void createChunk();
		void createTrees();
		void createPlants();

		GLuint getBlockAmount() const { return cubeVector.size(); }
		GLint getYPosition(GLint posX, GLint posZ);


	private:
		GLuint treeAmount, plantAmount;
		glm::vec3 chunkPos;

		std::unique_ptr<NoiseGenerator> noiseGenerator = nullptr;
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
		std::vector<std::unique_ptr<TreeGenerator>> treeVector;
		std::vector<std::unique_ptr<PlantGenerator>> plantVector;
};

#endif