#include"gameViewLayer.h"


void gameEngine::imguiSize(void* som) {
	ImGui::SliderFloat("float", &((gameEngine::GameViewLayer*)som)->size, 0.0f, 100.0f);
	std::cout << "yes";
}


void gameEngine::GameViewLayer::onAttach() {

	std::shared_ptr<gameEngine::Texture> tex = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture("floor.png", GL_TEXTURE_2D));
	std::shared_ptr < gameEngine::Material> som = std::make_shared < gameEngine::Material>(*new Material(tex));


	ShaderInit sompo;

	//std::shared_ptr <gameEngine::Shader> quadShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", ""));
	std::shared_ptr <gameEngine::Model> somLoad = std::make_shared <gameEngine::Model>(*new gameEngine::Model(gameEngine::Model::QUAD_MESH, glm::vec3(0.f, 0.f, 0.f), glm::vec3(90.f, 0.f, 0.f)));
	(somLoad)->setSize(size);
	somLoad->setMaterial(som);
	//layerRenderer->AddMeshCall(somLoad);
	somLoad->sendToRenderer(layerRenderer);
	//drawModel.push_back(somLoad);
	//std::dynamic_pointer_cast<gameEngine::Quad>(somLoad)->sendToRenderer(layerRenderer);
	gameEngine::getIMGUILayer()->addToMenu(new IMGUIJob{ &gameEngine::imguiSize,(void*)this });


	std::shared_ptr <gameEngine::Model> somLoad1 = std::make_shared <gameEngine::Model>(*new gameEngine::Model("objfile/spaceship.obj", glm::vec3(0.f, 10.f, 0.f), glm::vec3(0.f)));
	(somLoad1)->setSize(1.f);

	std::shared_ptr<gameEngine::Texture> rustex = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture("objfile/rustediron2_basecolor.png", GL_TEXTURE_2D));
	std::shared_ptr < gameEngine::Material> russom = std::make_shared < gameEngine::Material>(*new Material(rustex));

	somLoad1->setMaterial(russom);
	somLoad1->sendToRenderer(layerRenderer);


	/*std::shared_ptr <gameEngine::Model> somLoad2 = std::make_shared <gameEngine::Model>(*new gameEngine::Model("objfile/nanosuit/nanosuit.obj", glm::vec3(20.f, 0.f, 0.f), glm::vec3(0.f), modelShader));
	(somLoad2)->setSize(1.f);

	somLoad2->sendToRenderer(layerRenderer);*/


	//std::dynamic_pointer_cast<gameEngine::Model>(somLoad1)->sendToRenderer(layerRenderer);
	std::shared_ptr <gameEngine::Shader> lightShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("sceneLightVertexShader.glsl", "sceneLightFragmentShader.glsl", ""));
	std::vector< std::shared_ptr <gameEngine::Texture>> somtex;
	drawModel.push_back(somLoad1);
	//somtex.push_back(fbo->getTex(0));
	/*somtex.push_back(fbo->getTex(1));
	somtex.push_back(fbo->getTex(2));*/
	/*Light* sceneLight = (new Light(somtex, lightShader, true));
	fro->setLighting(sceneLight);
	sceneLight->addNewLight(glm::vec3(1.f, 1.f, -1.f), glm::vec3(0.f));*/

	//fro->addRenderObj(somLoad);
	//fro->addRenderObj(somLoad1);
	gameEngine::GameWindow::addToManager(cam);

	std::string vertShader2 = sompo.getVertShader(ShaderInit::TEX_COORDIN, ShaderInit::TEX_COORD);
	std::string fragShader2 = sompo.getFragShader(ShaderInit::TEX_COORD | ShaderInit::ALBEDO_TEX, ShaderInit::ALBEDO_COLOR);


	std::shared_ptr < gameEngine::Shader> finShader = std::make_shared < gameEngine::Shader>(*new gameEngine::Shader(vertShader2, fragShader2, ""));

	/*std::shared_ptr <gameEngine::Model> somLoad2 = std::make_shared<gameEngine::Model>(*new Model(*somLoad1.get()));
	somLoad2->setShader(finShader);
	(somLoad2)->setMaterial(som);
	GameWindow::addModel(somLoad2);*/
	
	gameEngine::GameWindow::addTex(fbo->getTex(0));
	gameEngine::GameWindow::setFinalShader(finShader);
	layerRenderer->createShader();
	fbo->check();

}