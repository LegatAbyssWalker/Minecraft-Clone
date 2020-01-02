#ifndef CUBEGENERATOR_H
#define CUBEGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Program.h"
#include "Texture.h"
#include "GLWindow.h"
#include "FileLocations.h"
#include "MoreInfo.h"

#include <iostream>
#include <vector>

class CubeGenerator {
	public:
		enum BlockType {
			Failed_Block = 0,
			Bedrock_Block = 1,
			Grass_Block = 2,
			Dirt_Block = 3,
			Stone_Block = 4,
			Sand_Block = 5,
			Leaf_Block = 6,
			Log_Block = 7,
			Cactus_Block = 8,
			Sandstone_Block = 9
		};

		CubeGenerator();

		void setType(CubeGenerator::BlockType blockType);
		void setTexture(std::shared_ptr<Texture> texture);
		void setScale(glm::vec3 scaleValue);
		void setPosition(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));

		void update();
		void render(GLWindow& glWindow, const glm::mat4 viewMatrix, const glm::mat4 projection);

		BlockType getBlockType() const { return blockType; }
		glm::vec3 getPosition() const { return glm::vec3(position); }
		
		glm::vec3 getP0() const { return getPosition() - scaleValue; } 
		glm::vec3 getP1() const { return getPosition() + scaleValue; }

	private:
		BlockType blockType;

		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;

		glm::vec3 position;
		glm::vec3 scaleValue = BLOCKS_SCALE_VALUE;
};

#endif