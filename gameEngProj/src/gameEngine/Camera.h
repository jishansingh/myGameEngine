#pragma once

#include"Shader.h"
#include"GameObject.h"
namespace gameEngine {
	class FUN_API Camera :public GameObj{
		glm::vec3 camPos;
		glm::mat4 viewMatrix;
		glm::vec3 worldUp;
		glm::vec3 camFront;
		glm::vec3 frontVec;
		float velOfRotation;
	public:
		Camera(glm::vec3 camPosition, const glm::vec3 faceTo = glm::vec3(0.f, 0.f, 0.f), const glm::vec3 upwardDir = glm::vec3(0.f, 1.f, 0.f));
		~Camera() {
		}
		void updateViewMatrix();
		void rotateCam(bool left);
		void onkeyPress(int key);

		void sendToShader(std::shared_ptr <Shader> shady);
		void sendCamPos(std::shared_ptr <Shader> shady, const std::string nam);
	};
}