#pragma once
#include"GameWindow.h"

extern gameEngine::GameWindow* gameEngine::createEngine();

int main(int argc, char* argv[]) {
	auto sand = gameEngine::createEngine();
	sand->render();
	delete sand;
}
