#ifndef PLAYINGSTATE_H
#define PLAYINGSTATE_H

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include <iostream>
#include <fstream>
#include <array>
#include <memory>
#include <vector>
#include <array>

#include "GLWindow.h"
#include "Mesh.h"
#include "Program.h"
#include "MoreInfo.h"
#include "FileLocations.h"
#include "Texture.h"
#include "CubeGenerator.h"
#include "Player.h"
#include "World.h"
#include "RayCasting.h"

class PlayingState : public State {
	public:
		PlayingState(StateMachine& machine, GLWindow& glWindow, bool replace = true);

		void updateEvents();
		void update();
		void render();

	private:
		std::unique_ptr<World> world = nullptr;
		std::unique_ptr<Player> player = nullptr;

		// Variables and Booleans
		GLboolean isPaused = false;

		// Timing
		GLfloat deltaTime = 0.f;
		GLfloat lastFrame;
};

#endif