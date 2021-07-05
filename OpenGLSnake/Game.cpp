#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"

const float snake[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};

const float tileVertices[]{
	-0.5f, -0.5f, 0.0f,

};


Game::Game() {
	window = Window("Snake game", 1920, 1080);
	gameState = GameState();
	camera = Camera(glm::vec3(0.0f, 3.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	// Set up OpenGL and window
	glfwSetInputMode(window.getId(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	tileVAO = genTileVAO();
}

static unsigned int genTileVAO() {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO = 

	unsignd int EBO = glGenEleme

	glBindVertexArray(0);

	return VAO;
}

void Game::drawBoard() const {

}

void Game::drawSnake() const {

}

void Game::drawFood() const {

}

void Game::processInput() {
	GLFWwindow* id = window.getId();
	if (glfwGetKey(id, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(id, true);
	}
	if (glfwGetKey(id, GLFW_KEY_W) == GLFW_PRESS) {

	}
	else if (glfwGetKey(id, GLFW_KEY_S) == GLFW_PRESS) {
	}
	else if (glfwGetKey(id, GLFW_KEY_D) == GLFW_PRESS) {
	}
	else if (glfwGetKey(id, GLFW_KEY_A) == GLFW_PRESS) {
	}
}

void Game::draw() const {
	drawBoard();
	drawSnake();
	drawFood();
}

void Game::play() {
	prevTime = (float) glfwGetTime();

	while (!glfwWindowShouldClose(window.getId())) {

		float currTime = (float)glfwGetTime();
		deltaTime += (currTime - prevTime);

		if (deltaTime > 0.5) {
			deltaTime -= 0.5;
			processInput();
			draw();
		}


		// Reseet the game
		if (gameState.isGameOver()) {
			gameState.reset();
			deltaTime = 0.0f;
			prevTime = (float) glfwGetTime();
		}
	}
}


