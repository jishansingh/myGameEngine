#pragma once
#include"GameWindow.h"

extern void gameEngine::createEngine(GameWindow* som);

GLint gameEngine::Texture::totalTexUnit = 0;

std::shared_ptr<gameEngine::Camera> gameEngine::Blur::quadCam;

bool gameEngine::pingPongFBO::horizontal;

int main(int argc, char* argv[]) {
	gameEngine::Blur::initCamera();
	gameEngine::pingPongFBO::initHorizon();
	gameEngine::GameWindow* som = new gameEngine::GameWindow("mywindow");
	gameEngine::createEngine(som);
	som->render();
	delete som;
	//delete gameEngine::Blur::quadCam;
}
