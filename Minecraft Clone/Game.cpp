#include "Game.h"
#include "MoreInfo.h"


void Game::run() {
	GLuint screenWidth = SCREEN_WIDTH;
	GLuint screenHeight = SCREEN_HEIGHT;

	glWindow = GLWindow(screenWidth, screenHeight, "Minecraft");
	glWindow.initWindow();

	machine.run(StateMachine::buildState<PlayingState>(machine, glWindow, true));

	while (!glWindow.getShouldClose()) {
		machine.nextState();
		machine.updateEvents();
		machine.update();
		machine.render();
	}
}
