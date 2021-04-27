#pragma once
#include"Camera.h"

gameEngine::Camera::Camera(glm::vec3 camPosition, const glm::vec3 faceTo, const glm::vec3 upwardDir)
	:camPos(camPosition), camFront(faceTo), worldUp(upwardDir) {
	updateViewMatrix();
	velOfRotation = 0.1f;
	frontVec = faceTo - camPosition;
	this->addKeyEvent(GLFW_KEY_W);
	this->addKeyEvent(GLFW_KEY_A);
	this->addKeyEvent(GLFW_KEY_S);
	this->addKeyEvent(GLFW_KEY_D);
	this->addKeyEvent(GLFW_KEY_Z);
	this->addKeyEvent(GLFW_KEY_X);
}

void gameEngine::Camera::updateViewMatrix() {
	viewMatrix = glm::mat4(1.f);
	viewMatrix = glm::lookAt(camPos, camFront, worldUp);
}
void gameEngine::Camera::rotateCam(bool left) {
	float angle = velOfRotation;
	if (left) {
		angle = -angle;
	}
	glm::mat4 tempMat(1.f);
	tempMat = glm::rotate(tempMat, glm::radians(angle), worldUp);
	glm::vec4 rotatedCam = tempMat * glm::vec4(frontVec, 0.f);
	frontVec = glm::vec3(rotatedCam.x, rotatedCam.y, rotatedCam.z);
	camFront = camPos + frontVec;
}
void gameEngine::Camera::onkeyPress(int key) {
	if (key == GLFW_KEY_W) {
		camPos += (frontVec) * 0.01f;
		camFront = camPos + frontVec;
	}
	else if (key == GLFW_KEY_S) {
		camPos -= (frontVec) * 0.01f;
		camFront = camPos + frontVec;
	}
	else if (key == GLFW_KEY_A) {
		rotateCam(false);
	}
	else if (key == GLFW_KEY_D) {
		rotateCam(true);
	}
	else if (key == GLFW_KEY_X) {
		camPos -= (worldUp) * 0.001f;
		camFront = camPos + frontVec;
	}
	else if (key == GLFW_KEY_Z) {
		camPos += (worldUp) * 0.001f;
		camFront = camPos + frontVec;
	}

}

void gameEngine::Camera::sendToShader(std::shared_ptr <Shader> shady) {
	updateViewMatrix();
	shady->setUniformMatrix4fv("viewMatrix", GL_FALSE, viewMatrix);
}
void gameEngine::Camera::sendCamPos(std::shared_ptr <Shader> shady, const std::string nam) {
	shady->setUniform3f(nam.c_str(), GL_FALSE, camPos);
}
