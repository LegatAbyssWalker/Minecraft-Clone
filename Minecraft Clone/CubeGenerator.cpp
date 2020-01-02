#include "CubeGenerator.h"


CubeGenerator::CubeGenerator()
	: mesh() {

	std::vector<GLfloat> cubeVertices {
		//    X  Y   Z   U     V  
		//  1
			-1, -1,  1, 0.25, 0.34,
			-1, -1, -1, 0.25, 0.66,
			-1,  1,  1, 0.00, 0.34,
			-1,  1,  1, 0.00, 0.34,
			-1,  1, -1, 0.00, 0.66,
			-1, -1, -1, 0.25, 0.66,

		//  2
			-1, -1, -1, 0.25, 0.66,
			-1, -1,  1, 0.25, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1, -1, -1, 0.50, 0.66,
			-1, -1, -1, 0.25, 0.66,

		//  3
			-1,  1, -1, 0.25, 1.00,
			-1, -1, -1, 0.25, 0.66,
			 1, -1, -1, 0.50, 0.66,
			 1, -1, -1, 0.50, 0.66,
			 1,  1, -1, 0.50, 1.00,
			-1,  1, -1, 0.25, 1.00,

		//  4
			-1,  1,  1, 0.25, 0.00,
			-1, -1,  1, 0.25, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1, -1,  1, 0.50, 0.34,
			 1,  1,  1, 0.50, 0.00,
			-1,  1,  1, 0.25, 0.00,

		//  5
			 1, -1,  1, 0.50, 0.34,
			 1, -1, -1, 0.50, 0.66,
			 1,  1,  1, 0.75, 0.34,
			 1,  1,  1, 0.75, 0.34,
			 1,  1, -1, 0.75, 0.66,
			 1, -1, -1, 0.50, 0.66,

		//  6
			-1,  1, -1, 1.00, 0.66,
			-1,  1,  1, 1.00, 0.34,
			 1,  1,  1, 0.75, 0.34,
			 1,  1,  1, 0.75, 0.34,
			 1,  1, -1, 0.75, 0.66,
			-1,  1, -1, 1.00, 0.66
	};

	mesh.createMesh(cubeVertices);
	program = Program::get(TERRAIN_VERTEX_SHADER, TERRAIN_FRAGMENT_SHADER);
}

void CubeGenerator::setType(CubeGenerator::BlockType blockType) {
	this->blockType = blockType;
}

void CubeGenerator::setTexture(std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

void CubeGenerator::setScale(glm::vec3 scaleValue) {
	this->scaleValue = scaleValue;
}

void CubeGenerator::setPosition(glm::vec3 position) {
	this->position = position;
}

void CubeGenerator::update() {
	// ?
}

void CubeGenerator::render(GLWindow& glWindow, const glm::mat4 viewMatrix, const glm::mat4 projection) {
	program->useProgram();

	// Model matrix
	glm::mat4 model(1.f);
	model = glm::translate(model, position);
	model = glm::scale(model, scaleValue);

	// View matrix
	glm::mat4 view = viewMatrix;

	// Uniforms
	program->setMat4("model", model);
	program->setMat4("view", view);
	program->setMat4("projection", projection);

	// Textures assignment
	texture->useTexture();

	// Rendering
	mesh.renderMesh();
}
