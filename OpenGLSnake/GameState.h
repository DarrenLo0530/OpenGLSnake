#pragma once

#include <vector>

const unsigned int GAMEBOARD_SIZE = 25;

const unsigned int BOARD_EMPTY = 0;
const unsigned int BOARD_SNAKE = 1;
const unsigned int BOARD_FOOD = 2;

class GameState {

public:
	GameState(unsigned int gameboardSize = GAMEBOARD_SIZE);

	// Getters
	unsigned int getScore() const;
	std::vector<std::vector<unsigned int>> getGameboard() const;

	// Setters
	void setGameboardSize(unsigned int gameboardSize);


	void clearBoard();
private:
	// Total number of points
	unsigned int score;

	// Stores the gamestate
	std::vector<std::vector<unsigned int>> gameboard;

};