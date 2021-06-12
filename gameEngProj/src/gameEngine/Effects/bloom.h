#pragma once
#include"Blur.h"

namespace gameEngine {
	class FUN_API Bloom :public EffectObj {
		std::shared_ptr<frameRenderObject> fro;
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr<Shader> brightShader;
		std::shared_ptr<Shader> shady;
		std::shared_ptr<Blur> blurEffect;
		std::shared_ptr<Texture> brightTex;
	public:
		Bloom():EffectObj() {
			blurEffect = std::make_shared<Blur>(*new Blur());
			brightTex = std::make_shared<Texture>(*new Texture(GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_FLOAT, 1024, 1024));
			brightShader = std::make_shared<Shader>(*new Shader("extractBrightVertexShader.glsl", "extractBrightFragmentShader.glsl", ""));
			shady = std::make_shared<Shader>(*new Shader("bloomVertexShader.glsl", "bloomFragmentShader.glsl", ""));
			fbo = std::make_shared<framebufferObject>(*new framebufferObject());
			fro = std::make_shared<frameRenderObject>(*new frameRenderObject(fbo, quadCam));
			fro->addRenderObj(somQuad);
			somQuad->setShader(brightShader);
		}

		void render(GLFWwindow* window, std::shared_ptr <Texture> tex, std::shared_ptr <Texture> resultTex) {
			somQuad->setShader(brightShader);
			fbo->addTexture(brightTex, 0);
			somQuad->replaceTex(0, tex);

			//fro->render(window);

			blurEffect->render(window, brightTex, brightTex);

			somQuad->setShader(shady);
			somQuad->replaceTex(0,tex);
			somQuad->replaceTex(1, brightTex);
			fbo->addTexture(resultTex, 0);
			//fro->render(window);

		}

	};
}


