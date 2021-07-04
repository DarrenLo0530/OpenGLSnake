#include "Camera.h"
#include <iostream>

glm::mat4 myLookAt(glm::vec3 pos, glm::vec3 front, glm::vec3 worldUp) {
	glm::vec3 right = glm::normalize(glm::cross(front, worldUp));
	glm::vec3 up = glm::normalize(glm::cross(right, front));
	glm::vec3 direction = -front;

	glm::mat4 rot = glm::mat4(1.0);
	rot[0][0] = right.x;
	rot[1][0] = right.y;
	rot[2][0] = right.z;
	rot[0][1] = up.x;
	rot[1][1] = up.y;
	rot[2][1] = up.z;
	rot[0][2] = direction.x;
	rot[1][2] = direction.y;
	rot[2][2] = direction.z;


	glm::mat4 trans = glm::mat4(1.0);
	trans[3][0] = -pos.x;
	trans[3][1] = -pos.y;
	trans[3][2] = -pos.z;

	return rot * trans;
}

Camera::Camera(glm::vec3 position, glm::vec3 front, glm::vec3 worldUp) {
	this->position = position;
	this->front = front;
	this->worldUp = worldUp;

	updateVectors();
}

Camera::Camera(float posX, float posY, float posZ, float frontX, float frontY, float frontZ, float worldUpX, float worldUpY, float worldUpZ) {
	this->position = glm::vec3(posX, posY, posZ);
	this->front = glm::vec3(frontX, frontY, frontZ);
	this->worldUp = glm::vec3(worldUpX, worldUpY, worldUpZ);

	updateVectors();
}

void Camera::processKeyboard(Camera_Movement direction, float deltaTime) { 
	const float adjustedSpeed = speed * deltaTime;
	
	glm::vec3 prevPosition = glm::vec3(position);
	if (direction == Camera_Movement::FORWARD) {
		position += glm::normalize(front) * adjustedSpeed;
	}
	else if (direction == Camera_Movement::BACKWARD) {
		position -= glm::normalize(front) * adjustedSpeed;
	}
	else if (direction == Camera_Movement::RIGHT) {
		position += glm::normalize(glm::cross(front, up)) * adjustedSpeed;
	}
	else {
		position -= glm::normalize(glm::cross(front, up)) * adjustedSpeed;
	}

	position.y = prevPosition.y;
}

void Camera::processScroll(float yOffset) {
	fov -= yOffset * zoomSensitivity;
	fov = glm::clamp(fov, 1.0f, 45.0f);
}
void Camera::processMouse(float xOffset, float yOffset) {
	yaw += xOffset * mouseSensitivity;
	pitch -= yOffset * mouseSensitivity;

	pitch = glm::clamp(pitch, -89.0f, 89.0f);

	updateVectors();
}

void Camera::updateVectors() {
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	front = glm::normalize(front);

	right = glm::normalize(glm::cross(front, worldUp));
	up = glm::normalize(glm::cross(right, front));
}

glm::mat4 Camera::getViewMatrix() const {
	//return myLookAt(position, front, worldUp);

	return glm::lookAt(position, position + front, up);

}