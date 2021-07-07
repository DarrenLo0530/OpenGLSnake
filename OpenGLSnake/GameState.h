#pragma once

#include <vector>
#include <utility>

const unsigned int GAMEBOARD_SIZE = 25;

const int BOARD_EMPTY = -1;
const int BOARD_FOOD = 0;
const int BOARD_TAIL = 1;

enum class SnakeMovement {
	LEFT,
	RIGHT,
	UP,
	DOWN,
};



class GameState {

public:
	GameState(unsigned int gameboardSize = GAMEBOARD_SIZE);

	// Getters
	unsigned int getScore() const;
	std::vector<std::vector<int>> getGameboard() const;
	unsigned int getGameboardSize() const;
	bool isGameOver() const;

	// Other methods
	void update(SnakeMovement movement);

	void reset();
private:

	// Head and tail of the snake
	std::pair<unsigned int, unsigned int> head;

	// Stores the gamestate
	std::vector<std::vector<int>> gameboard;

	// Total number of points
	unsigned int score;

	std::vector<std::pair<unsigned int, unsigned int>> emptySquares;

	// Amount of food that has been consumed and not been added to snake's length yet
	int foodConsumed;

	bool gameOver;

	void advancePosition(std::pair<unsigned int, unsigned int> position);

	int& getSquare(std::pair<unsigned int, unsigned int> position);

	void setFoodLocation();

	static std::pair<int, int> directionVectors[];
};