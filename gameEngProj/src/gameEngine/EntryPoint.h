#pragma once
#include"Texture.h"
#include"gameViewLayer.h"
#include"Effects/bloom.h"

//extern gameEngine::GameWindow* gameEngine::initGameWindow(const char* winNam, const int WINDOW_WIDTH, const int WINDOW_HEIGHT);
//extern void gameEngine::deleteWindow();
//extern void gameEngine::addToManager(std::shared_ptr <gameEngine::GameObj> somObj);
//extern void gameEngine::addTex(std::shared_ptr <gameEngine::Texture> po);
//extern void gameEngine::addLayer(std::shared_ptr <gameEngine::Layer> som);
//extern void gameEngine::setFinalShader(std::shared_ptr <gameEngine::Shader> shad);
//extern void gameEngine::renderWindow();
//extern void gameEngine::updateWindow();
//extern inline gameEngine::GameWindow* gameEngine::getWindow();
//extern GLFWwindow* gameEngine::getGLFWWindow();
//
//extern void gameEngine::getFrameSize(int& fwidth, int& fheight);

extern void gameEngine::createEngine();
std::shared_ptr<gameEngine::Camera> gameEngine::CommonUsed::quadCam;
std::shared_ptr<gameEngine::Quad> gameEngine::CommonUsed::somQuad;
std::shared_ptr<gameEngine::Cube> gameEngine::CommonUsed::somCube;




int main(int argc, char* argv[]) {
	
	gameEngine::pingPongFBO::initHorizon();
	gameEngine::initGameWindow("mywindow");
	gameEngine::Model::initModelLoader("");
	gameEngine::CommonUsed::initCamera();

	gameEngine::createEngine();
	gameEngine::renderWindow();
	gameEngine::deleteWindow();
	//delete gameEngine::EffectObj::quadCam;
}
