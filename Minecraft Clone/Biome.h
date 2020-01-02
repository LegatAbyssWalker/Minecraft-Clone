#ifndef BIOME_H
#define BIOME_H

#include "State.h"

class Biome {
	public:
		enum BiomeType {
			ForestBiome = 0,
			DesertBiome = 1,
			MountainBiome = 2
		};

		virtual void update() = 0;
		virtual void render(GLWindow& glWindow, glm::mat4 viewMatrix, glm::mat4 projection) = 0;
		
		virtual GLuint getBlockAmount() const = 0;

	protected:


};

#endif