//
// Created by Alteracia on 08.01.2021.
// For educational purpose. Use carefully.
//

#ifndef PARTICLES_GLFWENGINE_H
# define PARTICLES_GLFWENGINE_H

# include <glad/glad.h>
# include <stdexcept>
# include <vector>

# define GLFW_INCLUDE_NONE
# include <GLFW/glfw3.h>
# include "IComponent.h"

class GLFWEngine
{
public:
	GLFWEngine(std::vector<IComponent*> *behaves) : components(behaves)
	{
	}
	int init();
	void setInputCallbacks(GLFWscrollfun scroll,
						   GLFWmousebuttonfun mouse,
						   GLFWcursorposfun pointer,
						   GLFWkeyfun key);
	void loop();

	~GLFWEngine();

	static void GetWindowSize(int* width, int* height);
	void ChangeAnimation(int i);
private:
	static GLFWwindow			*window;
	std::vector<IComponent*>	*components;
	int refresh_flag = 0;

	void createWindow();
	void bindKeys(int key);
};


#endif
