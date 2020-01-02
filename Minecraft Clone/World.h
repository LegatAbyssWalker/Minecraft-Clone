#ifndef WORLD_H
#define WORLD_H

#include "State.h"
#include "GLWindow.h"
#include "Mesh.h"
#include "MoreInfo.h"
#include "FileLocations.h"
#include "GLWindow.h"
#include "Texture.h"



#include <iostream>
#include <vector>
#include <memory>

class World {
	public:
		World(GLWindow& glWindow);
	
		void update();
		void render(glm::mat4 viewMatrix);

		glm::mat4 getProjectionMatrix();
		
	private:
		GLsizei TOTAL_CHUNK_AMOUNT = 2; // MULTIPLE OF 2

		GLWindow& glWindow;

		glm::mat4 projectionMatrix;
};

#endif