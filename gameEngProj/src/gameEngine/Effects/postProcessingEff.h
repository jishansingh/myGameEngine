#pragma once
#include"gameEngine/libs.h"
#include"gameEngine/frameRenderObject.h"

namespace gameEngine {
	class FUN_API EffectObj {
	protected:
		static std::shared_ptr<gameEngine::Camera> quadCam;
	public:
		void static initCamera() {
			quadCam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
		}
		virtual void render(GLFWwindow* window, std::shared_ptr <Texture> tex, std::shared_ptr <Texture> resultTex) {}
	};
}

std::shared_ptr<gameEngine::Camera> gameEngine::EffectObj::quadCam;