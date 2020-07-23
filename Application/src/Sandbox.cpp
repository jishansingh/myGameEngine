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

void gameEngine::createEngine(GameWindow* som) {
	gameEngine::framebufferObject* fbo = new gameEngine::framebufferObject(1);
	gameEngine::Camera* cam = new gameEngine::Camera(glm::vec3(0.f, 0.f, 1.f));
	gameEngine::frameRenderObject* fro = new gameEngine::frameRenderObject(fbo,cam);
	gameEngine::Shader* modelShader = new gameEngine::Shader("modelVertexShader.glsl", "modelFragmentShader.glsl", "");
	gameEngine::modelLoader* somLoad = new gameEngine::modelLoader("objfile/nanosuit/nanosuit.obj", glm::vec3(0.f), glm::vec3(0.f), modelShader);
	fro->addRenderObj(somLoad);
	som->addFrameObj(fro);
	som->addToManager(cam);
	gameEngine::Shader* finShader = new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", "");
	//gameEngine::Texture* tex = new gameEngine::Texture("container.png", GL_TEXTURE_2D);
	som->addTex(fbo->textures[0]);
	som->setFinalShader(finShader);
}
