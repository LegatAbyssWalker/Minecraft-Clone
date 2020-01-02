#ifndef PLANTGENERATOR_H
#define PLANTGENERATOR_H

#include "State.h"
#include "Mesh.h"
#include "Program.h"
#include "Texture.h"
#include "GLWindow.h"
#include "FileLocations.h"
#include "MoreInfo.h"

#include <iostream>
#include <vector>

class PlantGenerator {
	public:
		enum PlantType {
			Shrub_Plant = 0,
			Rose_Plant = 1
		};

		PlantGenerator();

		void setTexture(std::shared_ptr<Texture> texture);
		void setScale(glm::vec3 scaleValue);
		void setPosition(glm::vec3 position = glm::vec3(0.f, 0.f, 0.f));
		void setType(PlantType plantType);

		void update();
		void render(GLWindow& glWindow, const glm::mat4 viewMatrix, const glm::mat4 projection);

		glm::vec3 getP0() const { return getPosition() - scaleValue; }
		glm::vec3 getP1() const { return getPosition() + scaleValue; }

		glm::vec3 getPosition() const { return glm::vec3(position); }


	private:
		PlantType plantType;

		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;

		glm::vec3 position;
		glm::vec3 scaleValue = PLANTS_SCALE_VALUE;
};

#endif