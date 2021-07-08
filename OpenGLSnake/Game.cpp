#include <glad\glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Game.h"

#include <stb_image.h>


const float BOARD_LEFT_BOUND = -1.0f;
const float BOARD_RIGHT_BOUND = 1.0f;
const float BOARD_TOP_BOUND = -1.0f;
const float BOARD_BOTTOM_BOUND = 1.0f;

const int DEFAULT_WIDTH = 1920;
const int DEFAULT_HEIGHT = 1080;

const float TICK_RATE = 0.3f;

Game::Game() {
	deltaTime = 0.0f;
	prevTime = 0.0f;

	// Set up window
	window = new Window("Snake game", DEFAULT_WIDTH, DEFAULT_HEIGHT);
	glfwSetInputMode(window->getId(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	// Set up OpenGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	shaderProgram = new Shader("shader.vert", "shader.frag");
	glfwSetFramebufferSizeCallback(window->getId(), framebufferSizeCallback);
	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, DEFAULT_WIDTH, DEFAULT_HEIGHT);

	// Set up 
	camera = new Camera(glm::vec3(0.0f, 2.3f, 0.9f), glm::vec3(0.0, -3.0, -1.0));
	gameState = new GameState();

	// VAOs
	tileVAO = genTileVAO();
	cubeVAO = genCubeVAO();


	// Textures
	boardTextureBlack = loadTexture("textures/black-tile.png", GL_RGBA);
	boardTextureWhite = loadTexture("textures/white-tile.png", GL_RGBA);
	snakeTexture = loadTexture("textures/snake.png", GL_RGBA);
	foodTexture = loadTexture("textures/food.png", GL_RGBA);
}


void Game::draw() {
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shaderProgram->use();

	glm::mat4 viewMatrix = camera->getViewMatrix();
	shaderProgram->setMatrix4fv("view", glm::value_ptr(viewMatrix));

	glm::mat4 projectionMatrix = glm::perspective(glm::radians(camera->fov), (float)window->getWidth() / window->getHeight(), 0.1f, 100.0f);
	shaderProgram->setMatrix4fv("projection", glm::value_ptr(projectionMatrix));

	glActiveTexture(GL_TEXTURE0);
	shaderProgram->setInt("texture1", 0);

	drawBoard();
	drawEntities();

	// Update screen
	glfwSwapBuffers(window->getId());
}


void Game::drawBoard() {
	const unsigned int gameboardSize = gameState->getGameboardSize();

	float tileX = (BOARD_RIGHT_BOUND - BOARD_LEFT_BOUND) / gameboardSize;
	float tileZ = (BOARD_BOTTOM_BOUND - BOARD_TOP_BOUND) / gameboardSize;

	glBindVertexArray(tileVAO);

	for (unsigned int i = 0; i < gameboardSize; i++) {
		for (unsigned int j = 0; j < gameboardSize; j++) {
			glm::mat4 tileTransform = glm::mat4(1.0f);
			tileTransform = glm::translate(tileTransform, glm::vec3(BOARD_LEFT_BOUND + tileX * j + tileX / 2.0f, 0.0f, BOARD_TOP_BOUND + tileZ * i + tileZ / 2.0f));
			tileTransform = glm::scale(tileTransform, glm::vec3(tileX, 1.0f, tileZ));
			shaderProgram->setMatrix4fv("model", glm::value_ptr(tileTransform));

			if (i % 2 == j % 2) {
				glBindTexture(GL_TEXTURE_2D, boardTextureBlack);
			}
			else {
				glBindTexture(GL_TEXTURE_2D, boardTextureWhite);
			}

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}

	glBindVertexArray(0);
}

void Game::drawEntities() {
	const unsigned int gameboardSize = gameState->getGameboardSize();

	float tileX = (BOARD_RIGHT_BOUND - BOARD_LEFT_BOUND) / gameboardSize;
	float tileZ = (BOARD_BOTTOM_BOUND - BOARD_TOP_BOUND) / gameboardSize;

	std::vector<std::vector<int>> gameboard = gameState->getGameboard();
	for (int i = 0; i < gameboard.size(); i++) {
		for (int j = 0; j < gameboard.at(i).size(); j++) {
			int currSquare = gameboard.at(i).at(j);

			glm::mat4 entityTransform = glm::mat4(1.0f);
			entityTransform = glm::translate(entityTransform, glm::vec3(BOARD_LEFT_BOUND + tileX * j + tileX / 2.0f, tileX / 2.0f, BOARD_TOP_BOUND + tileZ * i + tileZ / 2.0f));
			entityTransform = glm::scale(entityTransform, glm::vec3(tileX, tileX, tileZ));
			shaderProgram->setMatrix4fv("model", glm::value_ptr(entityTransform));


			if (currSquare == BOARD_FOOD) {
				glBindVertexArray(cubeVAO);
				glBindTexture(GL_TEXTURE_2D, foodTexture);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			}
			else if (currSquare != BOARD_EMPTY) {
				glBindVertexArray(cubeVAO);
				glBindTexture(GL_TEXTURE_2D, snakeTexture);
				glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
			}
		}
	}

	glBindVertexArray(0);
}

void Game::play() {
	prevTime = (float) glfwGetTime();

	while (!glfwWindowShouldClose(window->getId())) {
		// Clear 
		float currTime = (float)glfwGetTime();
		deltaTime += (currTime - prevTime);
		prevTime = currTime;
		processInput();

		if (deltaTime > TICK_RATE) {
			deltaTime -= TICK_RATE;
			gameState->update();
			draw();
		}

		// Reseet the game
		if (gameState->isGameOver()) {
			gameState->reset();
			deltaTime = 0.0f;
			std::cout << "BYE";
			prevTime = (float)glfwGetTime();
		}


		glfwPollEvents();

	}

	glfwTerminate();
}


void Game::processInput() {
	GLFWwindow* id = window->getId();
	if (glfwGetKey(id, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(id, true);
	}
	if (glfwGetKey(id, GLFW_KEY_W) == GLFW_PRESS) {
		gameState->setCurrentDirection(SnakeMovement::UP);
	}
	else if (glfwGetKey(id, GLFW_KEY_S) == GLFW_PRESS) {
		gameState->setCurrentDirection(SnakeMovement::DOWN);
	}
	else if (glfwGetKey(id, GLFW_KEY_D) == GLFW_PRESS) {
		gameState->setCurrentDirection(SnakeMovement::RIGHT);
	}
	else if (glfwGetKey(id, GLFW_KEY_A) == GLFW_PRESS) {
		gameState->setCurrentDirection(SnakeMovement::LEFT);
	}

}

void Game::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}