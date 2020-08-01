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
		//result = getFBO()->getTex(0);
		postEff["blur"]->render(window, getFBO()->getTex(0), result[0]);
	}
};

void gameEngine::createEngine(GameWindow* som) {
	std::shared_ptr<gameEngine::framebufferObject> fbo = std::make_shared<gameEngine::framebufferObject>(*new gameEngine::framebufferObject(1));
	std::shared_ptr <gameEngine::Camera> cam = std::make_shared < gameEngine::Camera>(*new gameEngine::Camera(glm::vec3(0.f, 0.f, 4.f)));
	std::shared_ptr <gameEngine::frameRenderObject> fro = std::make_shared <mySand>( *new mySand(fbo, cam));
	std::shared_ptr<gameEngine::EffectObj> slp = std::make_shared<gameEngine::Blur>(*new gameEngine::Blur());
	fro->addEffect("blur", slp);
	std::shared_ptr <gameEngine::Shader> modelShader    = std::make_shared <gameEngine::Shader>   ( *new gameEngine::Shader("modelVertexShader.glsl", "modelFragmentShader.glsl", ""));
	std::shared_ptr <gameEngine::ObjectRender> somLoad   = std::make_shared <gameEngine::modelLoader>  ( *new gameEngine::modelLoader("objfile/nanosuit/nanosuit.obj", glm::vec3(0.f), glm::vec3(0.f), modelShader));
	fro->addRenderObj(somLoad);
	som->addFrameObj(fro);
	som->addToManager(cam);
	std::shared_ptr < gameEngine::Shader> finShader = std::make_shared < gameEngine::Shader> (*new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", ""));
	//gameEngine::Texture* tex = new gameEngine::Texture("container.png", GL_TEXTURE_2D);
	fro->initializeAttachments(1);
	som->addTex(fro->result[0]);
	som->setFinalShader(finShader);
}
