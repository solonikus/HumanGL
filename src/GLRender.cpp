//
// Created by Alteracia on 05.01.2021.
// For educational purpose. Use carefully.
//

#include "GLRender.h"

int GLRender::Start()
{
	try
	{
		compileShader(GL_VERTEX_SHADER);
		compileShader(GL_FRAGMENT_SHADER);
		initShaderProgram();
	}
	catch (std::runtime_error &e)
	{
		printf("OpenGL ERROR: %s\n", e.what());
		return (EXIT_FAILURE);
	}
	glEnable(GL_DEPTH_TEST);
	return 0;
}


const char *vertexShaderSource = "#version 330 core\n"
								 "layout (location = 0) in vec3 aPos;\n"
								 "layout (location = 1) in vec3 aNorm;\n"
								 "uniform mat4 transform;\n"
								 "void main()\n"
								 "{\n"
								 "   gl_Position = transform * vec4(aPos, 1.0f);\n" //
								 "}\0";

const char *fragmentShaderSource = "#version 330 core\n"
								   "uniform vec4 color;\n"
								   "out vec4 FragColor;\n"
								   "void main()\n"
								   "{\n"
								   "	FragColor = color;\n"
								   "}\0";

void GLRender::compileShader(int type)
{
	int result;
	char infoLog[512];
	GLuint shader = glCreateShader(type);

	glShaderSource(shader, 1, &(type == GL_VERTEX_SHADER
	? vertexShaderSource : fragmentShaderSource), nullptr);

	glCompileShader(shader);
	glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		printf("%s", infoLog);
		throw std::runtime_error("Can't compile shader\n");
	}
	if (type == GL_VERTEX_SHADER)
		vertexShader = shader;
	else
		fragmentShader = shader;
}

void GLRender::initShaderProgram()
{
	int result;
	char infoLog[512];

	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &result);
	if (!result)
	{
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		printf("%s", infoLog);
		throw std::runtime_error("Can't link shader program\n");
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(shaderProgram); // TODO tutorial call this in loop
}

void GLRender::Update()
{
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

GLRender::~GLRender()
{
	cleanup();
}

void GLRender::cleanup()
{
	glDeleteProgram(shaderProgram);
}


void GLRender::Finish()
{

}

GLuint GLRender::shaderProgram = -1;
