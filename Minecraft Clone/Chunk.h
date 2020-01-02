#ifndef CHUNK_H
#define CHUNK_H

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

class Chunk {
	public:
		Chunk();

		void generateChunk();

	private:
		NoiseGenerator noiseGen;
};

#endif