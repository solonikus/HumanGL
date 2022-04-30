//
// Created by Alteracia on 11/5/21.
// For educational purpose. Use carefully.
//

#include "Renderer.h"
#include "GLFWEngine.h"
#include "GLRender.h"

void Renderer::Start()
{
	// Generate VAO VBO
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Bind
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Pass Vertices data
	glBufferData(GL_ARRAY_BUFFER, (int)(sizeof(GLfloat) * mesh.vertexSize
										* mesh.vertexCount), mesh.vertices, GL_STATIC_DRAW);
	// -- Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
						  (int)(mesh.vertexSize * sizeof(GLfloat)), nullptr);

	// -- Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
						  (int)(mesh.vertexSize * sizeof(GLfloat)),
						  (void *)((mesh.vertexSize - 3) * sizeof(GLfloat)));

	// Finish binding
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void Renderer::Update()
{
	//std::cout<<"Draw call\n";
	// Called each frame

	// 1. Pass transform to shader
	GLint transformLoc = glGetUniformLocation(GLRender::shaderProgram, "transform");
	int width;
	int height;
	GLFWEngine::GetWindowSize(&width, &height);
	Matrix<float> persp = Matrix<float>().Perspective(45.0f, (float)width, (float)height, 0.1F, 1000.0f);
	Matrix<float> result = transform->TransformMatrix(true).Translate(0.0f, 0.0f, -5.0f) * persp;
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, (float*)result.member);

	// 2. Pass color to shader
	GLint colorLoc = glGetUniformLocation(GLRender::shaderProgram, "color");
	glUniform4f(colorLoc, color.x, color.y, color.z, color.w);

	// 3. Render mesh glDraw
	glBindVertexArray(VAO);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glDrawArrays(GL_TRIANGLES, 0, mesh.vertexCount);
}



float cube[] = {
// back
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f,

0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,
-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f,

// up
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,

0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f,
0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,

// right
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f,
0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,

0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f,
0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f,

// front
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,

// down
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,

-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f,
-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,
0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f,

// left
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,

-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f,
-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f,
};

Mesh Renderer::DefaultCube()
{
	Mesh m = Mesh{
		36, 6, cube
	};
	return m;
}



Renderer::~Renderer() = default;

