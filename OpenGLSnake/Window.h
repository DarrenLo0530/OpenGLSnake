#pragma once
#include <string>
#include <glad\glad.h>
#include <GLFW/glfw3.h>

class Window
{
public: 
	Window(const std::string& title = "Game window", int width = 1920, int height = 1080);

	GLFWwindow* getId();

	int getHeight() const;
	int getWidth() const;

private:
	GLFWwindow* id;
};

