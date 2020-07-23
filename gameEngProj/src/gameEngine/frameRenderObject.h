#pragma once

#include"Core.h"
#include"GameWindow.h"
#include"framebufferObject.h"
#include"Events/EventManager.h"
#include"Camera.h"
#include"renderObj.h"

namespace gameEngine {
	class FUN_API frameRenderObject {
		framebufferObject* fbo;
		Camera* winCam;
	public:
		std::vector<ObjectRender*> renderObj;
		frameRenderObject(framebufferObject* fObj, Camera* cam) {
			fbo = fObj;
			winCam = cam;
		}

		inline void addRenderObj(ObjectRender* somObj) {
			renderObj.push_back(somObj);
		}

		~frameRenderObject() {
			delete winCam;
			for (int i = 0; i < renderObj.size(); i++) {
				delete renderObj[i];
			}
			delete fbo;
		}

		

		void render(GLFWwindow* window) {
			fbo->bind();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			//glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, 1024, 1024);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			for (int i = 0; i < renderObj.size(); i++) {
				//win->updateProjMatrix(renderObj[i]->getShader());
				//fbo->textures[0]->bind();
				renderObj[i]->getShader()->Use();
				renderObj[i]->updateModelMatrix();
				winCam->sendToShader(renderObj[i]->getShader());
				renderObj[i]->updateProjMatrix(window);
				renderObj[i]->Draw();
			}
			fbo->unBind();
		}
		unsigned int getFBO() {
			return fbo->getFBO();
		}
	};
}

