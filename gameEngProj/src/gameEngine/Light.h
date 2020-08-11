#pragma once

#include"libs.h"
#include"Core.h"
#include"frameRenderObject.h"

namespace gameEngine {


	class FUN_API Light :public CommonUsed, public GameObj {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> color;
		std::vector<float> power;
		std::vector<std::shared_ptr<Texture>>gbuffer;
		std::shared_ptr<Shader>shady;
		std::shared_ptr<frameRenderObject>fro;
		std::shared_ptr<ObjectRender>lightObj;
		std::shared_ptr <instancedRenderer>lightDraw;
	public:
		Light(std::vector<std::shared_ptr<Texture>>texBuffer, std::shared_ptr<Shader> lightShader,const bool draw = false) {
			gbuffer = texBuffer;
			shady = lightShader;
			std::shared_ptr <framebufferObject>fbo = std::make_shared<framebufferObject>(*new framebufferObject());
			fro = std::make_shared<frameRenderObject>(*new frameRenderObject(fbo, quadCam));
			fro->addRenderObj(somQuad);
			/*if (draw) {
				lightObj = std::make_shared<Cube>(*new Cube(glm::vec3(0.f)));
				lightDraw = std::make_shared <instancedRenderer>(*new instancedRenderer(lightObj));
			}*/
		}
		void render(GLFWwindow* window, std::shared_ptr <Texture> resultTex) {
			somQuad->setShader(shady);
			fro->getFBO()->addTexture(resultTex, 0);
			for (int i = 0; i < gbuffer.size(); i++) {
				somQuad->replaceTex(i, gbuffer[i]);
			}

			fro->render(window);
		}
		void Draw(std::shared_ptr<frameRenderObject>somFRO, GLFWwindow* window, std::shared_ptr <Texture> resultTex) {
			fro->getFBO()->addTexture(resultTex, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, somFRO->getFBO()->getFBO());
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fro->getFBO()->getFBO());
			glBlitFramebuffer(0, 0, 0, 0, 1024, 1024, 1024, 1024, GL_DEPTH_COMPONENT, GL_NEAREST);
			
			

			fro->render(window);
		}
		void onkeyPress(int keyNum) {
			
		}

	};
}

