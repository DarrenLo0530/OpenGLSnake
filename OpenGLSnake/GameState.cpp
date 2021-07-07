#include "GameState.h"


std::pair<int, int> GameState::directionVectors[] = { {-1, 0}, {1, 0}, {0, 1}, {0, -1} };

GameState::GameState(unsigned int gameboardSize) {
	gameboard.resize(gameboardSize, std::vector<int>(gameboardSize, BOARD_EMPTY));

	reset();
}


void GameState::update(SnakeMovement movement) {
	const unsigned int gameboardSize = getGameboardSize();
	std::pair<unsigned int, unsigned int> nextPosition;

	const unsigned int& headX = head.first;
	const unsigned int& headY = head.second;

	std::pair<int, int>& directionVector = directionVectors[(int) movement];
	
	const int& directionX = directionVector.first;
	const int& directionY = directionVector.second;

	nextPosition = { (headX + gameboardSize + directionX) % gameboardSize,
			(headY + gameboardSize + directionY) % gameboardSize };

	advancePosition(nextPosition);
}

int& GameState::getSquare(std::pair<unsigned int, unsigned int> position) {
	return gameboard.at(position.second).at(position.first);
}


void GameState::advancePosition(std:: pair<unsigned int, unsigned int> nextPosition) {
	int nextSquare = getSquare(nextPosition);

	// Check if snake collides with itself
	if (nextSquare >= BOARD_TAIL) {
		gameOver = true;
		return;
	}

	unsigned int& headX = head.first;
	unsigned int& headY = head.second;
	unsigned int snakeLength = getSquare(head);

	
	if (foodConsumed) {
		getSquare(nextPosition) = snakeLength + 1;
		foodConsumed--;
	}

	else {
		nextSquare = snakeLength;
		// Advance all body pieces forward
		
		unsigned int currX = headX;
		unsigned int currY = headY;

		const unsigned int gameboardSize = getGameboardSize();

		// Advance snakes body
		while (getSquare({ currX, currY }) != BOARD_TAIL) {
			for (int i = 0; i < 4; i++) {
				std::pair<int, int> directionVector = directionVectors[i];
				std::pair<unsigned int, unsigned int> nextBody = { (currX + gameboardSize + directionVector.first) % gameboardSize,
					(headY + gameboardSize + directionVector.second) % gameboardSize };
				if (getSquare(nextBody) == getSquare({ currX, currY }) - 1) {
					getSquare({ currX, currY })--;

					currX = nextBody.first;
					currY = nextBody.second;
				}
			}
		}

		// Add back tail to empty squares
		getSquare({ currX, currY }) = BOARD_EMPTY;
		emptySquares.push_back({ currX, currY });
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
	score = 0;
	foodConsumed = 0;
	gameOver = false;

	// Reset game board
	const unsigned int gameboardSize = getGameboardSize();
	gameboard.resize(gameboardSize, std::vector<int>(gameboardSize, BOARD_EMPTY));
	head = { gameboardSize / 2, gameboardSize / 2 };
	getSquare(head) = BOARD_TAIL;
	

	// Reset empty cells
	emptySquares.clear();
	for (unsigned int i = 0; i < gameboardSize; i++) {
		for (unsigned int j = 0; j < gameboardSize; j++) {
			emptySquares.push_back({ i, j });
		}
	}
}

// Getters
unsigned int GameState::getScore() const {
	return score;
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
