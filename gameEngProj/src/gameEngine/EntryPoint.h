#pragma once
#include"GameWindow.h"
#include"Effects/Blur.h"
#include"Effects/Bloom.h"
extern void gameEngine::createEngine(GameWindow* som);

GLint gameEngine::Texture::totalTexUnit = 0;



int main(int argc, char* argv[]) {
	
	gameEngine::pingPongFBO::initHorizon();
	gameEngine::GameWindow* som = new gameEngine::GameWindow("mywindow");
	gameEngine::EffectObj::initCamera();
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(som->getWindow(), true);
	ImGui_ImplOpenGL3_Init("#version 440");

	gameEngine::texOperation::initCamera();
	gameEngine::createEngine(som);
	som->render();
	delete som;
	//delete gameEngine::EffectObj::quadCam;
}
