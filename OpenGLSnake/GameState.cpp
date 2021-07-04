#include "GameState.h";

GameState::GameState(unsigned int gameboardSize) {
	setGameboardSize(gameboardSize);
}

// Getters
unsigned int GameState::getScore() const {
	return score;
}

std::vector<std::vector<unsigned int>> GameState::getGameboard() const {
	return gameboard;
}

// Setters
void GameState::setGameboardSize(unsigned int gameboardSize) {
	// Resize the gameboard
	gameboard.resize(gameboardSize, std::vector<unsigned int>(gameboardSize, BOARD_EMPTY));
}


void GameState::clearBoard() {
	const unsigned int gameboardSize = gameboard.size();
	gameboard.resize(gameboardSize, std::vector<unsigned int>(gameboardSize, BOARD_EMPTY));
}