#pragma once
#include"libs.h"
#include"Events/EventManager.h"
#include"Camera.h"
#include"renderObj.h"
void framebuffer_resize_callback(GLFWwindow* window, int width, int height);
namespace gameEngine{
	class FUN_API GameWindow {
	protected:
		GLFWwindow* window;
		EventManager* manager;
		//Camera* winCam;
		Camera* winCam;
		std::vector<Quad*> renderObj;
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
			glm::vec3 gop = glm::vec3(0.f, 0.f, 1.f);
			winCam =new Camera(gop);
			manager->addNewObj(winCam);
		}
		virtual ~GameWindow() {
			delete manager;
			for (int i = 0; i < renderObj.size(); i++) {
				delete renderObj[i];
			}
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
		void addRenderObj(Quad*iop) {
			renderObj.push_back(iop);
		}
		virtual void preRender(){}
		virtual void postRender() {}
		void render() {
			while (!glfwWindowShouldClose(window)) {
				glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
				manager->handleKeyboardInput(window);
				manager->handleKeyboardEvents();
				for (int i = 0; i < renderObj.size(); i++) {
					updateProjMatrix(renderObj[i]->getShader());
					winCam->sendToShader(renderObj[i]->getShader());
					renderObj[i]->updateModelMatrix();
					renderObj[i]->Draw();
				}

				preRender();
				postRender();
				glfwSwapBuffers(window);
				glfwPollEvents();

			}
		}

	};
	GameWindow* createEngine();
}
void framebuffer_resize_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}