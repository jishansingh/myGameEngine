#pragma once
#include"GameWindow.h"
#include"Renderer.h"
gameEngine::GameWindow* gameEngine::GameWindow::gameWin = NULL;
//export gameEngine::GameWindow* gameEngine::GameWindow::gameWin;

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

void gameEngine::GameWindow::initWindow() {
	glfwInit();
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVer);
	glfwWindowHint(GLFW_RESIZABLE, true);
}

void gameEngine::GameWindow::createWindow(const char* winName, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
	window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, winName, NULL, NULL);
	if (window == nullptr) {
		std::cout << "error in creating window";
		glfwTerminate();
	}
	framebufferheight = WINDOW_WIDTH;
	framebufferwidth = WINDOW_HEIGHT;
}

//gameEngine::GameWindow* initGameWindow(const char* winName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT) {
//	static gameEngine::GameWindow* som = NULL;
//	if (som == NULL) {
//		som = new gameEngine::GameWindow(winName, WINDOW_WIDTH, WINDOW_HEIGHT);
//	}
//
//	return som;
//}



gameEngine::GameWindow::GameWindow(const char* winName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT) {
	initWindow();
	createWindow(winName, WINDOW_WIDTH, WINDOW_HEIGHT);
	glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
	glfwSetFramebufferSizeCallback(window, framebuffer_resize_callback);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK) {
		std::cout << "ok";
		glfwTerminate();
	}
}
gameEngine::GameWindow::~GameWindow() {
	delete somLay;
	delete manager;
	glfwTerminate();
}
void gameEngine::GameWindow::updateProjMatrix(Shader* shady) {
	glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
	glm::mat4 projMatrix(1.f);
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	float fov = 45.f;
	projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
	shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
}

gameEngine::GameWindow* gameEngine::GameWindow::initGameWindow(const char* winName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT) {
	if (gameEngine::GameWindow::gameWin == NULL) {
		gameEngine::GameWindow::gameWin = new gameEngine::GameWindow(winName, WINDOW_WIDTH, WINDOW_HEIGHT);
		gameEngine::GameWindow::gameWin->initWindowLayer();
	}

	return gameEngine::GameWindow::gameWin;
}

void gameEngine::GameWindow::addModel(std::shared_ptr<Model> som) {
	som->sendToRenderer(gameEngine::GameWindow::gameWin->winRenderer);
}

gameEngine::ImGUILayer* gameEngine::getIMGUILayer() {
	return GameWindow::initGameWindow()->somLay;
}

void gameEngine::GameWindow::initWindowLayer() {
	//create Camera
	manager = new EventManager();

	//this camera is just for quad
	Camera* tempCam = new Camera(glm::vec3(0.f, 0.f, 1.f));
	winCam = std::make_shared<Camera>(*tempCam);

	//debug layer
	somLay = new ImGUILayer();

	somLay->onAttach();
	winRenderer = std::make_shared<Renderer>(*new Renderer(ALBEDO_TEX));
}



inline void gameEngine::GameWindow::addToManager(std::shared_ptr <GameObj> somObj) {
	initGameWindow()->manager->addNewObj(somObj);
}
void gameEngine::GameWindow::addTex(std::shared_ptr <Texture> po) {
	initGameWindow()->finTex.push_back(po);
}
void gameEngine::GameWindow::setFinalShader(std::shared_ptr <Shader> shad) {
	initGameWindow()->finalShader = shad;
	initGameWindow()->window2D = std::make_shared<Model>(*new Model(Model::QUAD_MESH, glm::vec3(0.f,0.f,0.f), glm::vec3(0.f)));
	std::shared_ptr<Material> som = std::make_shared<Material>(*new Material(initGameWindow()->finTex[0]));
	initGameWindow()->window2D->setMaterial(som);
	initGameWindow()->window2D->sendToRenderer(initGameWindow()->winRenderer);
}

inline gameEngine::GameWindow* gameEngine::GameWindow::getWindow() {
	return initGameWindow();
}

inline GLFWwindow* gameEngine::GameWindow::getGLFWWindow() {
	return initGameWindow()->window;
}

void gameEngine::GameWindow::update() {
	for (int i = 0; i < layerArr.size(); i++) {
		//updateProjMatrix(frameObj[i]->renderObj[0]->getShader());
		layerArr[i]->onUpdate();
	}
	somLay->onUpdate();
}


void gameEngine::GameWindow::render() {
	/*bool show_demo_window = true;
	bool show_another_window = false;
	ImVec4 clear_color = ImVec4(0.1f, 0.1f, 0.1f, 1.0f);
	float m_time = glfwGetTime();*/
	for (int i = 0; i < layerArr.size(); i++) {
		//updateProjMatrix(frameObj[i]->renderObj[0]->getShader());
		layerArr[i]->onAttach();
	}
	winRenderer->createShader();
	while (!glfwWindowShouldClose(window)) {
		manager->handleKeyboardInput(window);
		manager->handleKeyboardEvents();
		//glBindFramebuffer(GL_FRAMEBUFFER, 0);

		update();


		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		



		// Rendering


		

		//finalShader->Use();

		for (int i = 0; i < layerArr.size(); i++) {
			//updateProjMatrix(frameObj[i]->renderObj[0]->getShader());
			layerArr[i]->renderLayer();
		}

		glfwPollEvents();
		preRender();
		postRender();



		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		glViewport(0, 0, framebufferwidth, framebufferheight);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		glViewport(0, 0, framebufferwidth, framebufferheight);

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glDisable(GL_DEPTH_TEST);
		//glClear(GL_COLOR_BUFFER_BIT);

		/*glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);*/

		glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
		glViewport(0, 0, framebufferwidth, framebufferheight);
		//finalShader->Use();

		/*for (int i = 0; i < finTex.size(); i++) {
			finTex[i]->bind(i);
			std::string top = "texture" + std::to_string(i);
			finalShader->setUniform1i(top.c_str(), i);
		}*/
		//window2D->updateProjMatrix(window);
		//winCam->sendToShader(finalShader);

		winRenderer->Draw(winCam);

		/*window2D->updateModelMatrix();
		window2D->Draw();*/
		//finalShader->unUse();

		glfwPollEvents();




		// Rendering


		somLay->onUpdate();

		//finalShader->Use();




		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, framebufferwidth, framebufferheight);
		somLay->renderLayer();
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);



	}
	somLay->endLayer();
}

void gameEngine::GameWindow::renderWindow() {
	initGameWindow()->render();
}

void gameEngine::GameWindow::updateWindow() {
	//this will update all layers
	initGameWindow()->update();
}

void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	gameEngine::GameWindow::getWindow()->setFrameSize(width, height);
}

void gameEngine::GameWindow::addLayer(std::shared_ptr <gameEngine::Layer> som) {
	initGameWindow()->layerArr.push_back(som);
}
void gameEngine::GameWindow::getFrameSize(int& fwidth, int& fheight) {
	glfwGetFramebufferSize(initGameWindow()->window, &fwidth, &fheight);
	fwidth = initGameWindow()->framebufferwidth;
	fheight = initGameWindow()->framebufferheight;
}

void gameEngine::GameWindow::deleteWindow() {
	delete initGameWindow();
}