#include <iostream>

#include "Window.h"

Window::Window(const std::string &title, int width, int height) {
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

int Window::getHeight() const {
	int height;
	glfwGetWindowSize(id, NULL, &height);
	return height;
}

int Window::getWidth() const {
	int width;
	glfwGetWindowSize(id, &width, NULL);
	return width;
}


GLFWwindow* Window::getId() {
	return id;
}



