#pragma once
#include"postProcessingEff.h"
#include"gameEngine/Camera.h"
std::shared_ptr<gameEngine::Camera> gameEngine::CommonUsed::quadCam;
std::shared_ptr<gameEngine::Quad> gameEngine::CommonUsed::somQuad;
std::shared_ptr<gameEngine::Cube> gameEngine::CommonUsed::somCube;


void gameEngine::CommonUsed::initCamera() {
	somCube = std::make_shared <Cube>(*new Cube(glm::vec3(0.f), glm::vec3(0.f), 1.f, 1.f, 1.f));
	quadCam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
	somQuad = std::make_shared<Quad>(*new Quad(glm::vec3(0.f), glm::vec3(0.f), 0.5f, 0.5f, 0.f));
}
