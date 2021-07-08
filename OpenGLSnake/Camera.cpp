#include "Camera.h"

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp) {
	this->position = position;
	this->front = glm::normalize(front);
	this->worldUp = glm::normalize(worldUp);

	updateVectors();
}

Camera::Camera(float posX, float posY, float posZ, float frontX, float frontY, float frontZ, float worldUpX, float worldUpY, float worldUpZ) {
	Camera(glm::vec3(posX, posY, posZ), glm::vec3(frontX, frontY, frontZ), glm::vec3(worldUpX, worldUpY, worldUpZ));
}

void Camera::updateVectors() {
	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const {
	return glm::lookAt(position, position + front, up);

}