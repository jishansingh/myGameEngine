#pragma once

#include"Core.h"
#include"GameWindow.h"
#include"framebufferObject.h"
#include"Events/EventManager.h"
#include"Camera.h"
#include"renderObj.h"
#include"Effects/postProcessingEff.h"
namespace gameEngine {
	class FUN_API EffectObj;
	class FUN_API frameRenderObject :public sharedObj {
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr <Camera> winCam;
	protected:
		std::unordered_map<std::string,std::shared_ptr <EffectObj> > postEff;
	public:
		std::vector<std::shared_ptr<Texture>> result;
		std::vector< std::shared_ptr <ObjectRender>> renderObj;
		frameRenderObject(std::shared_ptr<framebufferObject> fObj, std::shared_ptr <Camera> cam) {
			fbo = fObj;
			winCam = cam;

		}

		inline void addRenderObj(std::shared_ptr <ObjectRender> somObj) {
			renderObj.push_back(somObj);
		}

		virtual ~frameRenderObject() {
		}

		void setUniformInt(char* name, int som) {
			for (int i = 0; i < renderObj.size(); i++) {
				renderObj[i]->getShader()->Use();
				renderObj[i]->getShader()->setUniform1i(name, som);
			}
		}

		void initializeAttachments(int noOfAttach) {
			for (int i = 0; i < noOfAttach; i++) {
				std::shared_ptr<Texture> temp = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture(GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_FLOAT, 1024, 1024));
				result.push_back(temp);
			}
		}

		virtual void setUniform(std::shared_ptr <Shader> shady) {}
		virtual void preRender() {}
		void addEffect(std::string temp,std::shared_ptr<EffectObj> somObj) {
			postEff[temp] = somObj;
		}

		virtual void effectApply(GLFWwindow* window){}
		void render(GLFWwindow* window) {
			fbo->bind();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, 1024, 1024);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			for (int i = 0; i < renderObj.size(); i++) {
				//win->updateProjMatrix(renderObj[i]->getShader());
				//fbo->textures[0]->bind();
				renderObj[i]->getShader()->Use();
				renderObj[i]->updateModelMatrix();
				winCam->sendToShader(renderObj[i]->getShader());
				renderObj[i]->updateProjMatrix(window);
				setUniform(renderObj[i]->getShader());
				renderObj[i]->Draw();
			}
			fbo->unBind();

			effectApply(window);

		}
		std::shared_ptr <framebufferObject> getFBO() {
			return fbo;
		}
	};
}

