#pragma once
#include "GameState.h";
#include "Window.h"

class Game
{
public:
	Game();
	void play();

private:
	Window window;
	GameState gameState;

	void gameLoop();
	void processInput();
};

