#include"MainHeader.h"

//class Sandbox :public gameEngine::GameWindow {
//public:
//	Sandbox():GameWindow("myWindow"){
//		gameEngine::Shader* shady = new gameEngine::Shader("quadVertexShader.glsl", "quadFragmentShader.glsl","");
//		std::vector<gameEngine::Texture*>tep;
//		gameEngine::Texture* tex = new gameEngine::Texture("container.png",GL_TEXTURE_2D,0);
//		gameEngine::Quad* temp = new gameEngine::Quad(glm::vec3(0.f),glm::vec3(0.f),0.5f,0.5f,shady, tep);
//		this->addRenderObj(temp);
//		temp->addTexture(tex);
//		gameEngine::Shader* modelShader = new gameEngine::Shader("modelVertexShader.glsl", "modelFragmentShader.glsl", "");
//
//		gameEngine::modelLoader* somLoad = new gameEngine::modelLoader("objfile/nanosuit/nanosuit.obj", glm::vec3(0.f), glm::vec3(0.f), modelShader);
//		this->addRenderObj(somLoad);
//
//	}
//	~Sandbox(){}
//
//};

class mySand :public gameEngine::frameRenderObject {
public:
	mySand(std::shared_ptr<gameEngine::framebufferObject> fbo, std::shared_ptr <gameEngine::Camera> cam)
		:frameRenderObject(fbo,cam)
	{
	}
	void effectApply(GLFWwindow* window) {
		//result[0] = getFBO()->getTex(0);
		//postEff["bloom"]->render(window, getFBO()->getTex(0), result[0]);
	}
};

void gameEngine::createEngine(GameWindow* som) {
	std::shared_ptr<gameEngine::GameViewLayer> glObj = std::make_shared<gameEngine::GameViewLayer>(*new gameEngine::GameViewLayer(som));

	som->addLayer(glObj);

	//std::shared_ptr <gameEngine::Shader> modelShader    = std::make_shared <gameEngine::Shader>   ( *new gameEngine::Shader("modelVertexShader.glsl", "modelFragmentShader.glsl", ""));
	
	//std::shared_ptr <gameEngine::ObjectRender> somLoad   = std::make_shared <gameEngine::modelLoader>  ( *new gameEngine::modelLoader("objfile/nanosuit/nanosuit.obj", glm::vec3(0.f), glm::vec3(0.f), modelShader));
	//std::shared_ptr <gameEngine::Shader> cubeShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("cubeVertexShader.glsl", "cubeFragmentShader.glsl", ""));
	//std::shared_ptr <gameEngine::ObjectRender> somLoad = std::make_shared <gameEngine::Cube>(*new gameEngine::Cube(glm::vec3(0.f), glm::vec3(0.f), 1.f, 1.f, 1.f, cubeShader));
	//std::shared_ptr <gameEngine::ObjectRender> inst = std::make_shared <gameEngine::instancedRenderer>(*new instancedRenderer(somLoad));
	//std::dynamic_pointer_cast<gameEngine::instancedRenderer>(inst)->addInstance(glm::vec3(0.f), glm::vec3(0.f));
	//std::dynamic_pointer_cast<gameEngine::instancedRenderer>(inst)->addInstance(glm::vec3(1.f), glm::vec3(0.f));
	
	
}
