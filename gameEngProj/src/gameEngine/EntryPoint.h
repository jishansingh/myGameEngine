#pragma once
#include"GameWindow.h"

extern void gameEngine::createEngine(GameWindow* som);

GLint gameEngine::Texture::totalTexUnit = 0;

int main(int argc, char* argv[]) {
	gameEngine::GameWindow* som = new gameEngine::GameWindow("mywindow");
	gameEngine::createEngine(som);
	som->render();
	delete som;
}
