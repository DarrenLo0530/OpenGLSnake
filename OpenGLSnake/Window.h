#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public: 
	Window(const std::string& title = "Game window", int width = 1920, int height = 1080);

	GLFWwindow* getId();
private:
	GLFWwindow* id;
};

