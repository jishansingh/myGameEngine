#pragma once
#include"GameWindow.h"



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
		std::cout << "no";
		glfwTerminate();
	}
	framebufferheight = WINDOW_WIDTH;
	framebufferwidth = WINDOW_HEIGHT;
}

gameEngine::GameWindow::GameWindow(const char* winName, const int WINDOW_WIDTH = 800, const int WINDOW_HEIGHT = 800) {
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

	//create Camera
	manager = new EventManager();

	//this camera is just for quad
	Camera* tempCam = new Camera(glm::vec3(0.f, 0.f, 1.f));
	winCam = std::make_shared<Camera>(*tempCam);

	somLay = new ImGUILayer(this);

	/*IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;*/

	//io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;         // We can honor GetMouseCursor() values (optional)
	//io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

	//io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
	//io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
	//io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
	//io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
	//io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
	//io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
	//io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
	//io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
	//io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
	//io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
	//io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
	//io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
	//io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
	//io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
	//io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
	//io.KeyMap[ImGuiKey_KeyPadEnter] = GLFW_KEY_KP_ENTER;
	//io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
	//io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
	//io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
	//io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
	//io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
	//io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

	//ImGui::StyleColorsDark();
	//manager->addNewObj(winCam);

	//ImGui_ImplGlfw_InitForOpenGL(window, true);
	//ImGui_ImplOpenGL3_Init("#version 440");
	somLay->onAttach();

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
inline void gameEngine::GameWindow::addFrameObj(std::shared_ptr <frameRenderObject> iop) {
	frameObj.push_back(iop);
}
inline void gameEngine::GameWindow::addToManager(std::shared_ptr <GameObj> somObj) {
	manager->addNewObj(somObj);
}
void gameEngine::GameWindow::addTex(std::shared_ptr <Texture> po) {
	finTex.push_back(po);
}
void gameEngine::GameWindow::setFinalShader(std::shared_ptr <Shader> shad) {
	this->finalShader = shad;
	Quad* tempQuad = new Quad(glm::vec3(0.f), glm::vec3(0.f), 0.5f, 0.5f, finalShader, 0.f);
	window2D = std::make_shared<Quad>(*tempQuad);
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
		finalShader->Use();

		for (int i = 0; i < finTex.size(); i++) {
			finTex[i]->bind();
			std::string top = "texture" + std::to_string(i);
			finalShader->setUniform1i(top.c_str(), finTex[i]->getTextureUnit());
		}
		window2D->updateProjMatrix(window);
		winCam->sendToShader(finalShader);

		window2D->updateModelMatrix();
		window2D->Draw();
		finalShader->unUse();

		




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
void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}