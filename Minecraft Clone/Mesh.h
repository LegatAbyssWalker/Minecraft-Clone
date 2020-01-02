#ifndef MESH_H
#define MESH_H

#include "GL/glew.h"

#include <iostream>
#include <vector>

class Mesh {
	public:
		Mesh();
		~Mesh();

		void createMesh(const std::vector<GLfloat>& vertices);
		void createMesh(const std::vector<GLfloat>& vertices, const std::vector<GLuint>& indices);
		void renderMesh();
		void clearMesh();

	private:
		std::vector<GLfloat> vertices;

		GLuint VAO, VBO, IBO;
		GLsizei indexCount;
};

#endif