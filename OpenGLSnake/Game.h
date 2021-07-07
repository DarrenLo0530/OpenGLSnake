#pragma once
#include "GameState.h"
#include "Window.h"
#include "Camera.h"
#include "Shader.h"

#include "Graphics.h"

class Game
{
public:
	Game();
	void play();

private:
	Window* window;
	GameState* gameState;
	Camera* camera;
	Shader* shaderProgram;

	void processInput();
	void draw() const;

	float deltaTime;
	float prevTime;

	void drawBoard() const;
	void drawEntities() const;

	unsigned int tileVAO;
	unsigned int cubeVAO;

	unsigned int boardTextureBlack;
	unsigned int boardTextureWhite;
	unsigned int snakeTexture;
	unsigned int foodTexture;


	static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

