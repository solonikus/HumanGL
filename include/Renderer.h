//
// Created by Alteracia on 11/5/21.
// For educational purpose. Use carefully.
//

#ifndef HUMAN_GL_RENDERER_H
#define HUMAN_GL_RENDERER_H

#include <glad/glad.h>

# include "IMonoBehavior.h"
# include "Transform.h"

struct Mesh
{
	int vertexCount;
	int vertexSize;
	float *vertices;
};

class Renderer : public IMonoBehavior
{
public:
	Renderer(Transform *component, Mesh mesh, Vector4<float> color) : transform(component), mesh(mesh), color(color){
		transform->AddBehaviour(this);
	}
	Renderer(Transform *component, Vector4<float> color) : transform(component), mesh(DefaultCube()), color(color){
		transform->AddBehaviour(this);
	}
	~Renderer() override;

	void Start() override;
	void Update() override;
private:
	static Mesh DefaultCube();

	Transform		*transform;
	Mesh			mesh;
	GLuint			VAO;
	GLuint			VBO;
	Vector4<float>	color;
};


#endif //HUMAN_GL_RENDERER_H
