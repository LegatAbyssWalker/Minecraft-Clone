#ifndef GAME_H
#define GAME_H

#include "State.h"
#include "StateMachine.h"
class StateMachine;

#include "PlayingState.h"

class Game {
	public:
		Game() = default;

		void run();

	private:
		StateMachine machine;
		GLWindow glWindow;
};

#endif