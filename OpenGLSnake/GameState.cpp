#include "GameState.h"
#include <iostream>

std::pair<int, int> GameState::directionVectors[] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };

GameState::GameState(unsigned int gameboardSize) {
	gameboard.resize(gameboardSize, std::vector<int>(gameboardSize, BOARD_EMPTY));
	reset();
}

void GameState::setCurrentDirection(SnakeMovement direction) {
	// Make it so that the snake can not go back in the opposite direction its head came from
	if (getSquare(head) == BOARD_TAIL || getSquare(getNextPosition(head, direction)) != getSquare(head) - 1) {
		currentDirection = direction;
	}
}

void GameState::update() {
	const unsigned int gameboardSize = getGameboardSize();
	std::pair<unsigned int, unsigned int> nextPosition;

	const unsigned int headX = head.first;
	const unsigned int headY = head.second;


	std::pair<int, int> directionVector = directionVectors[(int) currentDirection];
	const int directionX = directionVector.first;
	const int directionY = directionVector.second;



	nextPosition = { (headX + gameboardSize + directionX) % gameboardSize,
			(headY + gameboardSize + directionY) % gameboardSize };
	advancePosition(nextPosition);
}

int& GameState::getSquare(std::pair<unsigned int, unsigned int> position) {
	return gameboard.at(position.second).at(position.first);
}

std::pair<unsigned int, unsigned int> GameState::getNextPosition(std::pair<int, int> currPosition, SnakeMovement direction) {
	unsigned int gameboardSize = getGameboardSize();
	std::pair<int, int> directionVector = directionVectors[(int)direction];
	return { 
		(currPosition.first + gameboardSize + directionVector.first) % gameboardSize,
		(currPosition.second + gameboardSize + directionVector.second) % gameboardSize 
	};
}


void GameState::advancePosition(std:: pair<unsigned int, unsigned int> nextPosition) {
	int nextSquare = getSquare(nextPosition);

	// Check if snake collides with itself
	if (nextSquare >= BOARD_TAIL) {
		gameOver = true;
		return;
	}

	unsigned int headX = head.first;
	unsigned int headY = head.second;
	unsigned int snakeLength = getSquare(head);

	
	if (foodConsumed) {
		getSquare(nextPosition) = snakeLength + 1;
		foodConsumed--;
	}
	else {
		getSquare(nextPosition) = snakeLength;
		
		// Advance all body pieces forward
		
		std::pair<unsigned int, unsigned int> currPosition = head;

		const unsigned int gameboardSize = getGameboardSize();


		// Advance snakes body
		while (getSquare(currPosition) != BOARD_TAIL) {
			for (int i = 0; i < 4; i++) {
				std::pair<unsigned int, unsigned int> nextBody = getNextPosition(currPosition, (SnakeMovement)i);
				if (getSquare(nextBody) == getSquare(currPosition) - 1) {
					getSquare(currPosition)--;

					currPosition = nextBody;
				}
			}
		}

		// Add back tail to empty squares
		getSquare(currPosition) = BOARD_EMPTY;
		emptySquares.push_back(currPosition);
	}

	// Remove advanced to position from empty squares
	emptySquares.erase(std::remove(emptySquares.begin(), emptySquares.end(), nextPosition), emptySquares.end());
	// Reassign head of snake
	head = nextPosition;

	// Add to food consumed if the square just moved onto was a food square
	if (nextSquare == BOARD_FOOD) {
		foodConsumed++;
		setFoodLocation();
	}

}

void GameState::setFoodLocation() {
	unsigned int foodSquareIndex = rand() % emptySquares.size();

	std::pair<unsigned int, unsigned int> foodSquare = emptySquares.at(foodSquareIndex);

	getSquare(foodSquare) = BOARD_FOOD;
}

void GameState::reset() {
	// Reset stats
	foodConsumed = 0;
	gameOver = false;

	// Reset game board
	const unsigned int gameboardSize = getGameboardSize();
	gameboard.clear();
	gameboard.resize(gameboardSize, std::vector<int>(gameboardSize, BOARD_EMPTY));
	head = { gameboardSize / 2, gameboardSize / 2 };
	getSquare(head) = BOARD_TAIL;

	// Reset empty cells and exclude head
	emptySquares.clear();
	for (unsigned int i = 0; i < gameboardSize; i++) {
		for (unsigned int j = 0; j < gameboardSize; j++) {
			emptySquares.push_back({ i, j });
		}
	}
	emptySquares.erase(std::remove(emptySquares.begin(), emptySquares.end(), head), emptySquares.end());

	setFoodLocation();

	currentDirection = SnakeMovement::LEFT;
}

std::vector<std::vector<int>> GameState::getGameboard() const {
	return gameboard;
}

unsigned int GameState::getGameboardSize() const {
	return (unsigned int) gameboard.size();
}

bool GameState::isGameOver() const {
	return gameOver;
}
