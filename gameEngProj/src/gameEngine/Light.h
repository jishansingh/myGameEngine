#pragma once

#include"libs.h"
#include"Core.h"
#include"Camera.h"
#include"Shader.h"
#include"renderObj.h"
namespace gameEngine {

	class frameRenderObject;
	class FUN_API LightObj {
	public:
		glm::vec3* position;
		glm::vec3* color;
		float power = 0.f;
		LightObj(glm::vec3 pos, glm::vec3 col);

	};

	class FUN_API Light {
		std::vector<std::shared_ptr<LightObj>> lightArr;
		std::vector<std::shared_ptr<Texture>>gbuffer;
		std::shared_ptr<Shader>shady;
		std::shared_ptr<Shader>cubeShader;
		std::shared_ptr<frameRenderObject>fro;
		std::shared_ptr<frameRenderObject>drawFRO;
		std::shared_ptr<ObjectRender>lightObj;
		std::shared_ptr <instancedRenderer>lightDraw;
		bool drawLight = false;
	public:
		Light(std::vector<std::shared_ptr<Texture>>texBuffer, std::shared_ptr<Shader> lightShader, const bool draw = false);
		void render(GLFWwindow* window, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam);
		void addNewLight(glm::vec3 pos, glm::vec3 col);
		void update(int index);
		void Draw(GLFWwindow* window, std::shared_ptr<Texture>depthTex, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam);

	};
}

