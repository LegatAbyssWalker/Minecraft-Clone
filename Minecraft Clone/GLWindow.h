#ifndef GLWINDOW_H
#define GLWINDOW_H

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include <iostream>
#include <memory>

class GLWindow {
	public:
		GLWindow() = default;
		GLWindow(const GLuint screenWidth, const GLuint screenHeight, const char* windowTitle);
		~GLWindow();

		void initWindow();

		GLfloat getBufferWidth() { return bufferWidth; }
		GLfloat getBufferHeight() { return bufferHeight; }

		bool getShouldClose() { return glfwWindowShouldClose(window); }
		bool* getKeys() { return keys; }

		glm::vec2 getMousePosition() { return mousePosition; }

		GLfloat getXChange();
		GLfloat getYChange();

		void swapBuffers() { glfwSwapBuffers(window); }

	private:
		glm::vec2 mousePosition;

		GLFWwindow* window;

		const char* windowTitle;
		GLint screenWidth, screenHeight;
		GLint bufferWidth, bufferHeight;

		bool keys[1024];

		GLfloat lastX;
		GLfloat lastY;
		GLfloat xChange;
		GLfloat yChange;
		bool mouseFirstMoved;
		
		void createCallBacks();
		static void processKeyboard(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode);
		static void processMouse(GLFWwindow* window, GLdouble xPos, GLdouble yPos);
};

#endif