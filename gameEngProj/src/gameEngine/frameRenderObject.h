#pragma once

#include"Core.h"
#include"framebufferObject.h"
#include"Light.h"
#include"GameWindow.h"


namespace gameEngine {
	/*class LightBaseClass :public CommonUsed, public GameObj {
	public:
		virtual void render(GLFWwindow* window, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam){}
		virtual void Draw(GLFWwindow* window, std::shared_ptr<Texture>depthTex, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam) {}
		virtual ~LightBaseClass(){}
		virtual void onkeyPress(int keyNum) {
		}
	};*/
	class FUN_API frameRenderObject :public sharedObj {
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr <Camera> winCam;
		Light* sceneLight = NULL;
	protected:
		std::unordered_map<std::string,std::shared_ptr <EffectObj> > postEff;
	public:
		std::vector<std::shared_ptr<Texture>> result;
		std::vector< std::shared_ptr <ObjectRender>> renderObj;
		frameRenderObject(std::shared_ptr<framebufferObject> fObj, std::shared_ptr <Camera> cam) {
			fbo = fObj;
			winCam = cam;
		}

		frameRenderObject(std::shared_ptr<framebufferObject> fObj) {
			fbo = fObj;
		}
		inline void setCamera(std::shared_ptr <Camera> cam) {
			winCam = cam;
		}
		inline void setRenderObject(std::vector<std::shared_ptr<ObjectRender>> somObj) {
			renderObj = somObj;
		}
		inline void setLighting(Light* lig) {
			sceneLight = lig;
		}
		inline void addRenderObj(std::shared_ptr <ObjectRender> somObj) {
			renderObj.push_back(somObj);
		}

		virtual ~frameRenderObject() {
			delete sceneLight;
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
			//postEff[temp] = somObj;
		}

		virtual void effectApply(GLFWwindow* window){}

		void lightCalc() {
			if (sceneLight) {
				((Light*)sceneLight)->render(result[0], winCam);
				//((LightBaseClass*)sceneLight)->Draw(window, fbo->depthTex, result[0],winCam);
			}
		}
		void updateProjectionMat(std::shared_ptr <Shader> shady) {
			int framebufferwidth = 800;
			int framebufferheight = 800;
			fbo->bind();
			gameEngine::GameWindow::getFrameSize(framebufferwidth, framebufferheight);

			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 53.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}

		void render() {
			for (int i = 0; i < renderObj.size(); i++) {
				//win->updateProjMatrix(renderObj[i]->getShader());
				//fbo->textures[0]->bind();
				renderObj[i]->getShader()->Use();
				renderObj[i]->updateModelMatrix();
				winCam->sendToShader(renderObj[i]->getShader());
				updateProjectionMat(renderObj[i]->getShader());
				setUniform(renderObj[i]->getShader());
				renderObj[i]->Draw();
			}

		}
		std::shared_ptr <framebufferObject> getFBO() {
			return fbo;
		}
	};
}

