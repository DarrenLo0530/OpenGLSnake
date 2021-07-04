#include "Shader.h"

Shader::Shader(const char* vShaderPath, const char* fShaderPath){
	std::string vShaderStr;
	std::string fShaderStr;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	// Enable throwing exceptions
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		vShaderFile.open(vShaderPath);
		fShaderFile.open(fShaderPath);

		std::stringstream vShaderStream, fShaderStream;

		// Put file contents into string streamsc
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		// Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		// String stream to string	
		vShaderStr = vShaderStream.str();
		fShaderStr = fShaderStream.str();
	}
	catch (std::ifstream::failure e) {
		std::cout << "Error while reading shader file" << std::endl;
	}

	const char* vShaderCode = vShaderStr.c_str();
	const char* fShaderCode = fShaderStr.c_str();

	unsigned int vertexShader, fragmentShader;

	// Creating vertex shader
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vShaderCode, NULL);
	glCompileShader(vertexShader);

	checkCompilationErrors(vertexShader, "SHADER");

	// Creating fragment shader
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fShaderCode, NULL);
	glCompileShader(fragmentShader);

	checkCompilationErrors(fragmentShader, "SHADER");


	// Creating shader program
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	checkCompilationErrors(shaderProgram, "PROGRAM");

	// Clean up shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	ID = shaderProgram;
}

void Shader::use() {
	glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}	

void Shader::setInt(const std::string& name, int value) const {
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const {
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setMatrix4fv(const std::string& name, float* value) const {
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
}


void Shader::checkCompilationErrors(unsigned int shader, std::string type) {
	int success;
	char infoLog[1024];

	if (type == "PROGRAM") {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Error while linking shader program" << infoLog << std::endl;
		}
	}
	else {
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Errorr while compiling shader" << infoLog << std::endl;
		}
	}
}