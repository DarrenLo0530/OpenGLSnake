#pragma once
#include "GameState.h"
#include "Window.h"
#include "Camera.h"

class Game
{
public:
	Game();
	void play();

private:
	Window window;
	GameState gameState;
	Camera camera;

	unsigned int tileVAO;
	unsigned int foodVAO;
	unsigned int snakeVAO;

	void gameLoop();
	void processInput();
	void draw() const;

	float deltaTime;
	float prevTime;

	void drawBoard() const;
	void drawSnake() const;
	void drawFood() const;

	static unsigned int genTileVAO();
	static unsigned int genCubeVAO();

	static unsigned int genSnakeVAO();
	static unsigned int genFoodVAO()
};

