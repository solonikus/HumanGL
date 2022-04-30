//
// Created by Alteracia on 08.01.2021.
// For educational purpose. Use carefully.
//

#include "GLFWEngine.h"
#include "Transform.h"

int GLFWEngine::init()
{
	try
	{
		createWindow();
	}
	catch (std::runtime_error &e)
	{
		printf("GLFW ERROR: %s\n", e.what());
		return EXIT_FAILURE;
	}
	return 0;
}

void GLFWEngine::ChangeAnimation(int i)
{
	if (i == 1)
	{
		Transform	*human = static_cast<Transform*>(components->back());
		delete human;
		components->pop_back();
		components->push_back(createStandingHuman());
	}
	if (i == 2)
	{
				Transform	*human = static_cast<Transform*>(components->back());
		delete human;
		components->pop_back();
		components->push_back(createWalkingHuman());
	}
	if (i == 3)
	{
				Transform	*human = static_cast<Transform*>(components->back());
		delete human;
		components->pop_back();
		components->push_back(createJumpingHuman());
	}
	
}

void GLFWEngine::bindKeys(int key)
{
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_1:
		ChangeAnimation(1);
		refresh_flag = 1;
		break;
	case GLFW_KEY_2:
		ChangeAnimation(2);
		refresh_flag = 1;
		break;
	case GLFW_KEY_3:
		ChangeAnimation(3);
		refresh_flag = 1;
		break;
	default:
		break;
	}
}



void GLFWEngine::setInputCallbacks(GLFWscrollfun scroll,
							  GLFWmousebuttonfun mouse,
							  GLFWcursorposfun pointer,
							  GLFWkeyfun key)
{
	glfwSetScrollCallback(window, scroll);
	glfwSetMouseButtonCallback(window, mouse);
	glfwSetCursorPosCallback(window, pointer);
	glfwSetKeyCallback(window, 
						[](GLFWwindow* window, int key, int scancode, int action, int mode)
						{
							GLFWEngine *self = static_cast<GLFWEngine*>(glfwGetWindowUserPointer(window));
							self->bindKeys(key);
						}
						);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLFWEngine::createWindow()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	window = glfwCreateWindow(1280, 720, "Human GL", nullptr, nullptr);
	if (window == nullptr)
	{
		glfwTerminate();
		throw std::runtime_error("Can't create window");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetWindowUserPointer(window, this);
}

void GLFWEngine::loop()
{
	for (auto& b : *components) {
		if (b->Start() == EXIT_FAILURE)
			return;
	}
	while (!glfwWindowShouldClose(window))
	{
		if (refresh_flag)
		{
			for (auto& b : *components) {
				if (b->Start() == EXIT_FAILURE)
					return;
			}
			refresh_flag = 0;
		}

		for (auto& b : *components) {
			b->Update();
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	for (auto& b : *components) {
		b->Finish();
	}
}

GLFWEngine::~GLFWEngine()
{
	glfwTerminate();
}

void GLFWEngine::GetWindowSize(int *width, int *height)
{
	glfwGetWindowSize(window, width, height);
}

GLFWwindow* GLFWEngine::window = nullptr;


