//
// Created by Alteracia on 05.01.2021.
// For educational purpose. Use carefully.
//

#ifndef PARTICLES_GLRENDERER_H
#define PARTICLES_GLRENDERER_H

# include <glad/glad.h>
# include <stdexcept>

# include "IComponent.h"

class GLRender : public IComponent
{
public:
	~GLRender() override;

	int		Start() override;
	void	Update() override;
	void	Finish() override;
	static GLuint	shaderProgram;

private:
	GLuint			vertexShader;
	GLuint 			fragmentShader;

	void		compileShader(int type);
	void		initShaderProgram();
	void		cleanup();
};

#endif
