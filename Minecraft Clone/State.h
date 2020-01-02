#ifndef STATE_H
#define STATE_H

#include "GL/glew.h"

#include "GLFW/glfw3.h"
#include "GLFW/glfw3native.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "GLWindow.h"

#include <memory>

class StateMachine;

class State {
	public:
		State(StateMachine& machine, GLWindow& glWindow, bool replace = true);
		virtual ~State() = default;

		State(const State&) = delete;
		State& operator = (const State&) = delete;

		virtual void updateEvents() = 0;
		virtual void update() = 0;
		virtual void render() = 0;

		std::unique_ptr<State> nextState();

		bool isReplacing();

	protected:
		StateMachine& machine;
		GLWindow& glWindow;

		bool replacing;

		std::unique_ptr<State> next;
};

#endif