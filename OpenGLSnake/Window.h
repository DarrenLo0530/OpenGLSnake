#pragma once
#include <string>
#include <GLFW/glfw3.h>

class Window
{
public: 
	GLFWwindow* id;
	Window(const std::string& title = "Game window", int width = 1920, int height = 1080);
};

