#include "GLWindow.h"


GLWindow::GLWindow(const GLuint screenWidth, const GLuint screenHeight, const char* windowTitle)
	: screenWidth(screenWidth), screenHeight(screenHeight), windowTitle(windowTitle) {
	
	for (std::size_t x = 0; x < 1024; x++) { keys[x] = 0; }

	// VSync
	glfwSwapInterval(1);

}

GLWindow::~GLWindow() {
	glfwDestroyWindow(window);
	glfwTerminate();
}

void GLWindow::initWindow() {
	// Initialize GLFW
	if (glfwInit() != GLFW_TRUE) {
		std::cout << "GLFW init failed\n";
		glfwTerminate();
	}


	// Setup GLFW window properties 
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4); // Large version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4); // Small version 
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Detects any old OpenGL code, this will throw an error
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // Allows forward compatibility (between differnt OS) 


	// Creating window
	window = glfwCreateWindow(screenWidth, screenHeight, windowTitle, nullptr, nullptr);
	glfwSetWindowPos(window, 120, 80);

	if (window == nullptr) {
		std::cout << "GLFW window creation failed!\n";
		glfwTerminate();
	}

	// Get buffer size information
	glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);

	// Set context for GLEW to use (can change between which window)
	glfwMakeContextCurrent(window);

	// Mouse + Keyboard inputs
	glfwSetWindowUserPointer(window, this);
	createCallBacks();
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Allow modern extension features
	glewExperimental = GL_TRUE;


	if (glewInit() != GLEW_OK) {
		std::cout << "Glew init failed!\n";
		glfwDestroyWindow(window);
		glfwTerminate();
	}


	glEnable(GL_DEPTH_TEST);

	// Setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);
}

GLfloat GLWindow::getXChange() {
	GLfloat changedX = xChange;
	xChange = 0.f;
	return changedX;

	mousePosition.x = changedX;
}

GLfloat GLWindow::getYChange() {
	GLfloat changedY = yChange;
	yChange = 0.f;
	return changedY;

	mousePosition.x = changedY;
}

void GLWindow::createCallBacks() {
	glfwSetCursorPosCallback(window, processMouse);
	glfwSetKeyCallback(window, processKeyboard);
}

void GLWindow::processKeyboard(GLFWwindow* window, GLint key, GLint code, GLint action, GLint mode) {
	GLWindow& glWindow = *static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }

	if (key >= 0 && key < 1024) {
		if (action == GLFW_PRESS) {
			glWindow.keys[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			glWindow.keys[key] = false;
		}
	}
}

void GLWindow::processMouse(GLFWwindow* window, GLdouble xPos, GLdouble yPos) {
	GLWindow& glWindow = *static_cast<GLWindow*>(glfwGetWindowUserPointer(window));

	if (glWindow.mouseFirstMoved) {
		glWindow.lastX = xPos;
		glWindow.lastY = yPos;
		glWindow.mouseFirstMoved = false;
	}

	// Finds last coordinates
	glWindow.xChange += xPos - glWindow.lastX;
	glWindow.yChange += glWindow.lastY - yPos;

	// Updates current coordinates
	glWindow.lastX = xPos;
	glWindow.lastY = yPos;
}