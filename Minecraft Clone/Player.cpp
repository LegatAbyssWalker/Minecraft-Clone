#include "Player.h"

Player::Player(GLWindow& glWindow, glm::vec3 position, glm::mat4 projection) 
	: rayCast(glWindow, camera, projection) {
	
	std::vector<GLfloat> crosshairVertices {
		//   X      Y   Z   U     V 
		// Horizontal
			-1.0,  0.2, 0, 0.00, 0.50,
			-1.0, -0.2, 0, 0.00, 0.50,
			 1.0,  0.2, 0, 1.00, 0.50,
			 1.0,  0.2, 0, 1.00, 0.50,
			-1.0, -0.2, 0, 0.00, 0.50,
			 1.0, -0.2, 0, 1.00, 0.50,

		// Verticle
			 0.2,  1.0, 0, 0.50, 1.00,
			-0.2,  1.0, 0, 0.50, 1.00,
			-0.2, -1.0, 0, 0.50, 0.00,
			-0.2, -1.0, 0, 0.50, 0.00,
			 0.2, -1.0, 0, 0.50, 0.00,
			 0.2,  1.0, 0, 0.50, 1.00
	};

	mesh.createMesh(crosshairVertices);
	program = Program::get(BASIC_VERTEX_SHADER, BASIC_FRAGMENT_SHADER);
	texture = Texture::get(CROSSHAIR_TEXTURE_LOCATION);

	// Camera
	camera = Camera(position, glm::vec3(0.f, 1.f, 0.f), -90.f, 0.f, 5.f, 0.3f);
}

void Player::updateEvents(GLWindow& glWindow) {
	// Camera event updates
	camera.processKeyboard(glWindow.getKeys(), deltaTime);
	camera.processMouseMovement(glWindow.getXChange(), glWindow.getYChange());
}

void Player::update(GLfloat deltaTime) {
	this->deltaTime = deltaTime;
	rayCast.update();

	//std::cout << rayCast.getCurrentRay().x << " : " << rayCast.getCurrentRay().y << " : " << rayCast.getCurrentRay().z << '\n';
}

void Player::render() {
	program->useProgram();

	// Model matrix
	glm::mat4 model(1.f);
	model = glm::translate(model, glm::vec3(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0));
	model = glm::scale(model, glm::vec3(8.f));

	// View matrix
	glm::mat4 view = glm::mat4(1.f);
	
	// Projection matrix for crosshair
	glm::mat4 projection = glm::ortho(0.f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.f, -1.0f, 1.0f);

	// Uniforms
	program->setMat4("model", model);
	program->setMat4("view", view);
	program->setMat4("projection", projection);

	// Texture assignment
	texture->useTexture();

	// Rendering
	mesh.renderMesh();
}
