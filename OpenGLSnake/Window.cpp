#include <GLFW/glfw3.h>
#include <iostream>

#include "Window.h"

Window::Window(std::string &title, int width, int height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	id = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

	if (id == NULL) {
		std::cout << "Unable to create window" << std::endl;
		glfwTerminate();
	}

	glfwMakeContextCurrent(id);
}


