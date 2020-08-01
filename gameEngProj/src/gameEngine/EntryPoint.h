#pragma once
#include"GameWindow.h"
#include"Effects/Blur.h"
extern void gameEngine::createEngine(GameWindow* som);

GLint gameEngine::Texture::totalTexUnit = 0;



int main(int argc, char* argv[]) {
	gameEngine::EffectObj::initCamera();
	gameEngine::pingPongFBO::initHorizon();
	gameEngine::GameWindow* som = new gameEngine::GameWindow("mywindow");
	gameEngine::texOperation::initCamera();
	gameEngine::createEngine(som);
	som->render();
	delete som;
	//delete gameEngine::EffectObj::quadCam;
}
