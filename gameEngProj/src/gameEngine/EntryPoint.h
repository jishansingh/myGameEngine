#pragma once
#include"GameWindow.h"
#include"Texture.h"
#include"Effects/Blur.h"
#include"Effects/Bloom.h"
extern void gameEngine::createEngine(GameWindow* som);


int main(int argc, char* argv[]) {
	
	gameEngine::pingPongFBO::initHorizon();
	gameEngine::GameWindow* som = new gameEngine::GameWindow("mywindow",800,800);
	gameEngine::CommonUsed::initCamera();

	gameEngine::createEngine(som);
	som->render();
	delete som;
	//delete gameEngine::EffectObj::quadCam;
}
