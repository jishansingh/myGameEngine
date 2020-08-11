#pragma once
#include"gameEngine/libs.h"
#include"gameEngine/frameRenderObject.h"

namespace gameEngine {
	class FUN_API CommonUsed {
	protected:
		static std::shared_ptr<gameEngine::Camera> quadCam;
		static std::shared_ptr<Quad> somQuad;
	public:
		void static initCamera() {
			quadCam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			somQuad = std::make_shared<Quad>(*new Quad(glm::vec3(0.f), glm::vec3(0.f), 0.5f, 0.5f, 0.f));
		}
	};
	class FUN_API EffectObj: public CommonUsed {
	public:
		virtual void render(GLFWwindow* window, std::shared_ptr <Texture> tex, std::shared_ptr <Texture> resultTex) {}
	};
}

std::shared_ptr<gameEngine::Camera> gameEngine::CommonUsed::quadCam;
std::shared_ptr<gameEngine::Quad> gameEngine::CommonUsed::somQuad;