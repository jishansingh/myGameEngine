#pragma once

#include"libs.h"
#include"Core.h"
#include"Effects/postProcessingEff.h"
namespace gameEngine {

	class frameRenderObject;
	class GameViewLayer;
	class FUN_API LightObj {
	public:
		glm::vec3* position;
		glm::vec3* color;
		float power = 0.f;
		LightObj(glm::vec3 pos, glm::vec3 col);

	};

	class FUN_API Light {

		enum lightType {
			BLING_PHONG=1,
			OTHER=2
		};

		std::vector<std::shared_ptr<LightObj>> lightArr;
		std::vector<std::shared_ptr<Texture>>gbuffer;

		std::shared_ptr<GameViewLayer>lightShader;



		std::shared_ptr<Shader>shady;
		std::shared_ptr<Shader>cubeShader;
		std::shared_ptr<frameRenderObject>fro;
		std::shared_ptr<frameRenderObject>drawFRO;
		std::shared_ptr<ObjectRender>lightObj;
		std::shared_ptr <Model>lightDraw;
		bool drawLight = false;
	public:
		Light(std::vector<std::shared_ptr<Texture>>texBuffer, std::shared_ptr<Shader> lightShader, const bool draw = false);
		void render(std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam);
		void addNewLight(glm::vec3 pos, glm::vec3 col);
		void update(int index);
		void Draw(GLFWwindow* window, std::shared_ptr<Texture>depthTex, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam);

	};
}

