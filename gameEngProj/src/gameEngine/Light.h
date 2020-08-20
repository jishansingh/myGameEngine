#pragma once

#include"libs.h"
#include"Core.h"
#include"frameRenderObject.h"

namespace gameEngine {

	class frameRenderObject;
	class FUN_API Light : public LightBaseClass {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> color;
		std::vector<float> power;
		std::vector<std::shared_ptr<Texture>>gbuffer;
		std::shared_ptr<Shader>shady;
		std::shared_ptr<Shader>cubeShader;
		std::shared_ptr<frameRenderObject>fro;
		std::shared_ptr<frameRenderObject>drawFRO;
		std::shared_ptr<ObjectRender>lightObj;
		std::shared_ptr <instancedRenderer>lightDraw;
		bool drawLight = false;
	public:
		Light(std::vector<std::shared_ptr<Texture>>texBuffer, std::shared_ptr<Shader> lightShader,const bool draw = false) {
			gbuffer = texBuffer;
			shady = lightShader;
			std::shared_ptr <framebufferObject>fbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
			std::shared_ptr <framebufferObject>tempfbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
			fro = std::make_shared<frameRenderObject>(*new frameRenderObject(fbo, quadCam));
			drawFRO = std::make_shared<frameRenderObject>(*new frameRenderObject(tempfbo));
			fro->addRenderObj(somQuad);
			drawLight = draw;
			if (draw) {
				cubeShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("simpleCubeVertexShader.glsl", "simpleCubeFragmentShader.glsl", ""));
				lightObj = somCube;
				lightDraw = std::make_shared <instancedRenderer>(*new instancedRenderer(lightObj));
				drawFRO->addRenderObj(lightDraw);
			}
		}
		void render(GLFWwindow* window, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam) {
			somQuad->setShader(shady);
			fro->getFBO()->addTexture(resultTex, 0);
			for (int i = 0; i < gbuffer.size(); i++) {
				somQuad->replaceTex(i, gbuffer[i]);
			}
			shady->setUniform1i("noOfLight", positions.size());
			for (int i = 0; i < positions.size(); i++) {
				std::string temp = "sceneLight[" + std::to_string(i) + "]";
				shady->setUniform3f((temp + ".position").c_str(),GL_FALSE, positions[i]);
				shady->setUniform3f((temp + ".color").c_str(), GL_FALSE, color[i]);
			}
			sceneCam->sendCamPos(shady,"camPos");
			glDisable(GL_DEPTH_TEST);
			fro->render(window);
		}
		void addNewLight(glm::vec3 pos, glm::vec3 col) {
			positions.push_back(pos);
			color.push_back(col);
		}
		void update() {
			lightDraw->updateData(positions, color);
		}
		void Draw(GLFWwindow* window, std::shared_ptr<Texture>depthTex, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam) {
			drawFRO->getFBO()->bind();
			somCube->setShader(cubeShader);
			cubeShader->Use();
			somCube->setSize(0.1f);
			drawFRO->getFBO()->setDepthTex(depthTex);
			drawFRO->getFBO()->addTexture(resultTex, 0);
			drawFRO->setCamera(sceneCam);
			drawFRO->getFBO()->check();
			update();
			glEnable(GL_DEPTH_TEST);
			if (drawLight) {
				lightDraw->getShader()->Use();
				lightDraw->updateModelMatrix();
				sceneCam->sendToShader(lightDraw->getShader());
				lightDraw->updateProjMatrix(window);
				lightDraw->Draw();
				//drawFRO->render(window);
			}
			glDisable(GL_DEPTH_TEST);
			somCube->setSize(1.f);
			drawFRO->getFBO()->unBind();
		}

	};
}

