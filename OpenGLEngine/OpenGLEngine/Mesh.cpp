#pragma warning( push )
#pragma warning( disable : 4201)
#pragma warning( disable : 4310)
#include <gl_core_4_4.h>
#include <GLFW\glfw3.h>
#pragma warning( pop )
#include "Mesh.h"
#include <Shader.h>

Mesh::~Mesh()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteBuffers(1, &ibo);
}

void Mesh::initaliseQuad()
{
	assert(vao == 0);

	glGenBuffers(1, &vbo);
	glGenVertexArrays(1, &vao);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	Vertex vertices[6];
	vertices[0].position = { -0.5f, 0, 0.5f, 1 };
	vertices[1].position = { -0.5f, 0, 0.5f, 1 };
	vertices[2].position = { -0.5f, 0, 0.5f, 1 };
	
	vertices[3].position = { -0.5f, 0, 0.5f, 1 };
	vertices[4].position = { -0.5f, 0, 0.5f, 1 };
	vertices[5].position = { -0.5f, 0, 0.5f, 1 };

	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(Vertex),
		vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE,
		sizeof(Vertex), 0);


	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	triCount = 2;
}

void Mesh::draw()
{
	glBindVertexArray(vao);

	if (ibo != 0)
		glDrawElements(GL_TRIANGLES, 3 * triCount,
			GL_UNSIGNED_INT, 0);
	else
		glDrawArrays(GL_TRIANGLES, 0, 3 * triCount);

	aie::ShaderProgram shader;

	shader.loadShader(aie::eShaderStage::VERTEX,
		"./shaders/simple.vert");

	shader.loadShader(aie::eShaderStage::FRAGMENT,
		"./shader/simple.frag");

	if(shader.link() == false)
	{
		printf("Shader Error: %s\n", shader.getLastError());
	}
}