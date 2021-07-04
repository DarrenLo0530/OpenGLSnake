#pragma once
#include <string>

class Window
{
public: 
	GLFWwindow* id;
	Window(std::string& title, int width, int height);
};

