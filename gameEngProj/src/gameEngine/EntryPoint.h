#pragma once
#include"GameWindow.h"
#include"Texture.h"
#include"Effects/bloom.h"
extern void gameEngine::createEngine(GameWindow* som);
std::shared_ptr<gameEngine::Camera> gameEngine::CommonUsed::quadCam;
std::shared_ptr<gameEngine::Quad> gameEngine::CommonUsed::somQuad;
std::shared_ptr<gameEngine::Cube> gameEngine::CommonUsed::somCube;



int main(int argc, char* argv[]) {
	
	gameEngine::pingPongFBO::initHorizon();
	gameEngine::GameWindow* som = new gameEngine::GameWindow("mywindow",800,800);
	gameEngine::CommonUsed::initCamera();

	gameEngine::createEngine(som);
	som->render();
	delete som;
	//delete gameEngine::EffectObj::quadCam;
}
