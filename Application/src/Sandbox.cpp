#include"MainHeader.h"

class Sandbox :public gameEngine::GameWindow {
public:
	Sandbox():GameWindow("myWindow"){
		gameEngine::Shader* shady = new gameEngine::Shader("quadVertexShader.glsl", "quadFragmentShader.glsl","");
		std::vector<gameEngine::Texture*>tep;
		gameEngine::Quad* temp = new gameEngine::Quad(glm::vec3(0.f),glm::vec3(0.f),0.5f,0.5f,shady, tep);
		this->addRenderObj(temp);
	}
	~Sandbox(){}

};

gameEngine::GameWindow* gameEngine::createEngine() {
	return new Sandbox();
}