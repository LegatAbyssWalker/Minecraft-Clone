#ifndef PLAYER_H
#define PLAYER_H

#include "State.h"
#include "Camera.h"
#include "GLWindow.h"
#include "MoreInfo.h"
#include "Program.h"
#include "Mesh.h"
#include "Texture.h"
#include "FileLocations.h"
#include "RayCasting.h"

#include <iostream>
#include <memory>

class Player {
	public:
		Player(GLWindow& glWindow, glm::vec3 position, glm::mat4 projection);

		void updateEvents(GLWindow& glWindow);
		void update(GLfloat deltaTime);
		void render();

		glm::mat4 getViewMatrix() { return camera.calculateViewMatrix(); }
		const glm::vec3 getPosition() { return camera.getPosition(); }
		glm::vec3 getRayCast() { return rayCast.getCurrentRay(); }

	private:
		GLfloat deltaTime;

		Camera camera;
		GLfloat lastX = SCREEN_WIDTH / 2.f;
		GLfloat lastY = SCREEN_HEIGHT / 2.f;
		bool firstMouse = true;

		RayCasting rayCast;

		Mesh mesh;
		std::shared_ptr<Program> program;
		std::shared_ptr<Texture> texture;
};

#endif