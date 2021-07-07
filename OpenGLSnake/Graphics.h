#pragma once
#include <string>
#include <glad/glad.h>

unsigned int genTileVAO();
unsigned int genCubeVAO();

unsigned int loadTexture(const std::string& textureFile, GLenum format);