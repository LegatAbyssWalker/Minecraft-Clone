#include "State.h"


State::State(StateMachine& machine, GLWindow& glWindow, bool replace)
	: machine{ machine }
	, glWindow{ glWindow }
	, replacing{ replace } {
}

std::unique_ptr<State> State::nextState() {
	return std::move(next);
}

bool State::isReplacing() {
	return replacing;
}
