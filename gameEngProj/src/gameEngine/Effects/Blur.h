#pragma once

#include"postProcessingEff.h"
#include"gameEngine/ImpOperation.h"

namespace gameEngine {

	class FUN_API pingPongFBO :public frameRenderObject {
		static bool horizontal;
	public:
		pingPongFBO(std::shared_ptr <framebufferObject> fbo, std::shared_ptr <Camera> cam)
			:frameRenderObject(fbo, cam) {
		}
		void setUniform(std::shared_ptr <Shader> shady) {
			shady->setUniform1i("horizontal", horizontal);
			horizontal = !horizontal;
		}
		static void initHorizon() {
			horizontal = false;
		}
	};
	
	class FUN_API Blur :public EffectObj {
		std::shared_ptr <frameRenderObject>pingpongfro[2];
		std::shared_ptr <Shader> shady;
		std::shared_ptr<Quad> tempQuad;
	public:
		Blur() {
			shady = std::make_shared<Shader>(*new Shader("pingPongBlurVertexShader.glsl", "pingPongBlurFragmentShader.glsl", ""));
			//(std::dynamic_pointer_cast<Quad>(somQuad))->addTexture(tex);
			//tempQuad = std::make_shared<Quad>(*new Quad(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f), 0.5f, 0.5f, 0.f));
			for (int i = 0; i < 2; i++) {
				std::shared_ptr <framebufferObject> tempfbo = std::make_shared<framebufferObject>(*new framebufferObject(1, false));
				pingpongfro[i] = std::make_shared<frameRenderObject>(*new pingPongFBO(tempfbo, quadCam));
				pingpongfro[i]->addRenderObj(somQuad);
			}
		}
		

		void render(GLFWwindow* window, std::shared_ptr <Texture> tex, std::shared_ptr <Texture> resultTex) {
			(std::dynamic_pointer_cast<Quad>(somQuad))->replaceTex(0,tex);
			somQuad->setShader(shady);
			const int noOfIteration = 4;
			for (int k = 0; k < noOfIteration; k++) {
				for (int i = 0; i < 2; i++) {
					if (k == noOfIteration - 1 && i == 1) {
						pingpongfro[i]->getFBO()->addTexture(resultTex, 0);
					}
					pingpongfro[i]->render(window);
					(std::dynamic_pointer_cast<Quad>(somQuad))->replaceTex(0, pingpongfro[i]->getFBO()->getTex(0));
				}
			}
			//return pingpongfro[1]->getFBO()->textures[0];
		}

		~Blur() {
		}
	};
}


bool gameEngine::pingPongFBO::horizontal;
