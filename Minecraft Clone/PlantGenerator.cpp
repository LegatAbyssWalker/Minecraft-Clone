#include "PlantGenerator.h"

PlantGenerator::PlantGenerator()
	: mesh() {

	std::vector<GLfloat> shrubVertices{
		//  X   Y   Z   U      V  
		// 1
			1,  1,  1, 0.98, 0.98,
		   -1, -1, -1, 0.00, 0.00,
		   -1,  1, -1, 0.00, 0.98,

		// 2
		   -1, -1, -1, 0.00, 0.00,
		    1,  1,  1, 0.98, 0.98,
			1, -1,  1, 0.98, 0.00,
		
		// 3
		   -1, -1,  1, 0.00, 0.00,
		   -1,  1,  1, 0.00, 0.98,
		    1,  1, -1, 0.98, 0.99,

		// 4
		   -1, -1,  1, 0.00, 0.00,
			1,  1, -1, 0.98, 0.98,
			1, -1, -1, 0.98, 0.00
	};


	mesh.createMesh(shrubVertices);
	program = Program::get(TERRAIN_VERTEX_SHADER, TERRAIN_FRAGMENT_SHADER);
}

void PlantGenerator::setTexture(std::shared_ptr<Texture> texture) {
	this->texture = texture;
}

void PlantGenerator::setScale(glm::vec3 scaleValue) {
	this->scaleValue = scaleValue;
}

void PlantGenerator::setPosition(glm::vec3 position) {
	this->position = position;
}

void PlantGenerator::setType(PlantType plantType) {
	this->plantType = plantType;
}

void PlantGenerator::update() {
	// ? 
}

void PlantGenerator::render(GLWindow& glWindow, const glm::mat4 viewMatrix, const glm::mat4 projection) {
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

	// Texture assignment
	texture->useTexture();

	// Rendering
	mesh.renderMesh();
}
