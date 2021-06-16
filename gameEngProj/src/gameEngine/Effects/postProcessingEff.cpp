#pragma once
#include"postProcessingEff.h"
#include"gameEngine/Camera.h"
std::shared_ptr<gameEngine::Camera> gameEngine::CommonUsed::quadCam;


void gameEngine::CommonUsed::initCamera() {
	quadCam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
}
