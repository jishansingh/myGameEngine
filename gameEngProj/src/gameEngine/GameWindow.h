#pragma once
#include"libs.h"
#include"Events/EventManager.h"
#include"Camera.h"
#include"renderObj.h"
#include"frameRenderObject.h"
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

			//create Camera
			manager = new EventManager();

			//this camera is just for quad
			winCam = new Camera(glm::vec3(0.f, 0.f, 1.f));

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
			while (!glfwWindowShouldClose(window)) {
				glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				//glEnable(GL_DEPTH_TEST);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
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
				
				//glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				for (int i = 0; i < finTex.size(); i++) {
					finTex[i]->bind();
					std::string top = "texture" + std::to_string(i);
					finalShader->setUniform1i(top.c_str(), finTex[i]->getTextureUnit());
				}
				finalShader->Use();
				window2D->updateProjMatrix(window);
				winCam->sendToShader(finalShader);

				window2D->updateModelMatrix();
				
				window2D->Draw();

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