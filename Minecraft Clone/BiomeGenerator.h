#ifndef BIOMEGENERATOR_H
#define BIOMEGENERATOR_H

#include "State.h"
#include "CubeGenerator.h"
#include "GLWindow.h"
#include "NoiseGenerator.h"
#include "Random.h"
#include "Frustum.h"

#include <iostream>
#include <memory>
#include <vector>
#include <array>
#include <algorithm>

class BiomeGenerator {
	public:
		enum class BiomeType {
			forest, 
			desert,
			mountain
		};

		BiomeType getBiomeTypeAt(glm::vec3 position);

	private:
		NoiseGenerator biomeNoise;
};

#endif