#pragma once
#include"gameEngine/libs.h"
#include"gameEngine/Camera.h"
#include"gameEngine/renderObj.h"
#include"gameEngine/Texture.h"

namespace gameEngine {
	class FUN_API CommonUsed {
	public:
		static std::shared_ptr<Camera> quadCam;
		static void initCamera();
	};
	class FUN_API EffectObj: public CommonUsed {
	public:
		virtual void render(GLFWwindow* window, std::shared_ptr <Texture> tex, std::shared_ptr <Texture> resultTex) {}
	};
}
//std::shared_ptr<gameEngine::Camera> gameEngine::CommonUsed::quadCam;
//std::shared_ptr<gameEngine::Quad> gameEngine::CommonUsed::somQuad;
//std::shared_ptr<gameEngine::Cube> gameEngine::CommonUsed::somCube;
