#include "Mesh.h"

Mesh::Mesh() {
	VAO = 0;
	VBO = 0;
	IBO = 0;
	indexCount = 0;
}

Mesh::~Mesh() {
	clearMesh();
}

void Mesh::createMesh(const std::vector<GLfloat>& vertices) {
	this->vertices = vertices;

	// Binding
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Information
	// VBO Information
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertices.size(), vertices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, (void*)(sizeof(GLuint) * 3));
	glEnableVertexAttribArray(1);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices) {
	indexCount = indices.size();

	// Binding
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// Information
	// VBO Information
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLuint) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	// IBO Information
	glGenBuffers(1, &IBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * indices.size(), indices.data(), GL_STATIC_DRAW);


	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(GLuint) * 5, (void*)(sizeof(GLuint) * 3));
	glEnableVertexAttribArray(1);

	// Unbinding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::renderMesh() {
	// Binding
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);

	// Rendering
	if (indexCount > 0) { glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0); }
	else { glDrawArrays(GL_TRIANGLES, 0, vertices.size()); }

	// Unbinding
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Mesh::clearMesh() {
	if (VAO != 0) {
		glDeleteVertexArrays(1, &VAO);
		VAO = 0;
	}

	if (VBO != 0) {
		glDeleteBuffers(1, &VBO);
		VBO = 0;
	}

	if (IBO != 0) {
		glDeleteBuffers(1, &IBO);
		IBO = 0;
	}

	indexCount = 0; 
}
