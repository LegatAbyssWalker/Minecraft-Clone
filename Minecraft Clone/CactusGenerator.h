#ifndef CACTUSGENERATOR_H
#define CACTUSGENERATOR_H

#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "Random.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class CactusGenerator {
	public:
		CactusGenerator() = default;
		CactusGenerator(glm::vec3 position);

		void update();
		void render(GLWindow & glWindow, glm::mat4 viewMatrix, glm::mat4 projection, const Frustum & frustum);

		glm::vec3 getPosition() const { return cubeVector[0]->getPosition(); }

	private:
		Random<> random;
		std::vector<std::unique_ptr<CubeGenerator>> cubeVector;
};

#endif