#pragma once
#include"libs.h"
#include"Events/EventManager.h"
#include"Camera.h"
#include"renderObj.h"
#include"frameRenderObject.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
namespace gameEngine{
	class FUN_API GameWindow {
	protected:
		GLFWwindow* window;
		EventManager* manager;
		Quad* window2D;
		Shader* finalShader;
		Camera* winCam;
		Texture* testTex;
		//Camera* winCam;
		std::vector<Texture*>finTex;
		std::vector<frameRenderObject*> frameObj;
	private:
		int glMajorVer = 4;
		int glMinorVer = 4;

		int framebufferheight;
		int framebufferwidth;
		void initWindow() {
			glfwInit();
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, glMajorVer);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, glMinorVer);
			glfwWindowHint(GLFW_RESIZABLE, true);
		}
		void createWindow(const char* winName, int WINDOW_WIDTH, int WINDOW_HEIGHT) {
			window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, winName, NULL, NULL);
			if (window == nullptr) {
				std::cout << "no";
				glfwTerminate();
			}
			framebufferheight = WINDOW_WIDTH;
			framebufferwidth = WINDOW_HEIGHT;
		}
	public:
		GameWindow(const char* winName, const int WINDOW_WIDTH = 800, const int WINDOW_HEIGHT = 800) {
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

			/*IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;

			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(window, true);
			ImGui_ImplOpenGL3_Init("version 440");*/

			//create Camera
			manager = new EventManager();

			//this camera is just for quad
			winCam = new Camera(glm::vec3(0.f, 0.f, 1.f));
			//ImGui::StyleColorsDark();
			//manager->addNewObj(winCam);
		}
		virtual ~GameWindow() {
			delete manager;
			for (int i = 0; i < frameObj.size(); i++) {
				delete frameObj[i];
			}
			delete winCam;
			delete window2D;
			glfwTerminate();
		}
		virtual void updateProjMatrix(Shader*shady) {
			glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 45.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}
		inline void addFrameObj(frameRenderObject*iop) {
			frameObj.push_back(iop);
		}
		inline void addToManager(GameObj* somObj) {
			manager->addNewObj(somObj);
		}
		void addTex(Texture* po) {
			finTex.push_back(po);
		}
		void setFinalShader(Shader* shad) {
			this->finalShader = shad;
			window2D = new Quad(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f), 0.5f, 0.5f, finalShader,0.f);
		}
		virtual void preRender(){}
		virtual void postRender() {}
		void render() {
			bool show_demo_window = true;
			bool show_another_window = false;
			ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
			while (!glfwWindowShouldClose(window)) {
				//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				//glEnable(GL_DEPTH_TEST);
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				//ImGui_ImplOpenGL3_NewFrame();
				//ImGui_ImplGlfw_NewFrame();
				//ImGui::NewFrame();

				//if (show_demo_window)
				//	ImGui::ShowDemoWindow(&show_demo_window);

				//// 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
				//{
				//	static float f = 0.0f;
				//	static int counter = 0;

				//	ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

				//	ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
				//	ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
				//	ImGui::Checkbox("Another Window", &show_another_window);

				//	ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
				//	ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

				//	if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				//		counter++;
				//	ImGui::SameLine();
				//	ImGui::Text("counter = %d", counter);

				//	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
				//	ImGui::End();
				//}
				//// 3. Show another simple window.
				//if (show_another_window)
				//{
				//	ImGui::Begin("Another Window", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
				//	ImGui::Text("Hello from another window!");
				//	if (ImGui::Button("Close Me"))
				//		show_another_window = false;
				//	ImGui::End();
				//}

				manager->handleKeyboardInput(window);
				manager->handleKeyboardEvents();
				//glBindFramebuffer(GL_FRAMEBUFFER, 0);
				for (int i = 0; i < frameObj.size(); i++) {
					//updateProjMatrix(frameObj[i]->renderObj[0]->getShader());
					frameObj[i]->render(window);
				}

				glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
				glViewport(0, 0, framebufferwidth, framebufferheight);

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
				glBindVertexArray(0);
				glBindTexture(GL_TEXTURE_2D, 0);
				glEnable(GL_DEPTH_TEST);
				//finalShader->Use();
				
				glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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


				//ImGui::Render();

				preRender();
				postRender();
				glfwSwapBuffers(window);
				glfwPollEvents();

			}
		}
		GLFWwindow* getWindow() {
			return window;
		}
	};
	void createEngine(GameWindow* som);
}
void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}