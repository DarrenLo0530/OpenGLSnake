#include "Graphics.h"

#include <glad/glad.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

unsigned int genVAO(const float vertices[], size_t verticesSize,  const unsigned int indices[], size_t indicesSize) {
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesSize, indices, GL_DYNAMIC_DRAW);

	glBindVertexArray(0);

	return VAO;
}

unsigned int genTileVAO() {
	const float tileVertices[]{
		-0.5f, 0.0f, 0.5f, 0.0f, 0.0f,  // Bottom left
		 0.5f, 0.0f, 0.5f, 1.0f, 0.0f,  // Bottom right
		 0.5f, 0.0f, -0.5f, 1.0f, 1.0f, // Top right
		-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, // Top left
	};

	const unsigned int tileIndices[]{
		0, 1, 2, 0, 2, 3
	};


	return genVAO(tileVertices, sizeof(tileVertices), tileIndices, sizeof(tileIndices));
}

unsigned int genCubeVAO() {
	const float cubeVertices[]{
		// Front
		-0.5f, -0.5f, 0.5f, 0.25f, 0.0f,  // Bottom left 0
		 0.5f, -0.5f, 0.5f, 0.5f, 0.0f,  // Bottom right 1
		 0.5f, 0.5f, 0.5f, 0.5f, 1.0f, // Top right 2
		-0.5f, 0.5f, 0.5f, 0.25f, 1.0f, // Top left 3

		// Back
		-0.5f, -0.5f, -0.5f, 0.75f, 0.0f,  // Bottom left 4
		 0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // Bottom right 5
		 0.5f, 0.5f, -0.5f, 1.0f, 1.0f, // Top right 6
		-0.5f, 0.5f, -0.5f, 0.75f, 0.0f, // Top left 7
	};

	const unsigned int cubeIndices[]{
		// Front
		0, 1, 2, 0, 2, 3,
		// Top
		3, 2, 7, 2, 6, 7, 
		//Bottom
		0, 1, 4, 4, 5, 1,
		// Right
		2, 6, 5, 5, 1, 2,
		// Left
		7, 3, 0, 0, 4, 7,
		// Back
		4, 5, 6, 4, 6, 7,
	};
	return genVAO(cubeVertices, sizeof(cubeVertices), cubeIndices, sizeof(cubeIndices));
}

unsigned int loadTexture(const std::string& textureFile, GLenum format) {
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	
	// Set texture options
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, numColourChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(textureFile.c_str(), &width, &height, &numColourChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << stbi_failure_reason() << std::endl;
	}

	stbi_image_free(data);
	return texture;
}