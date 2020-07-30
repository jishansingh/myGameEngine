#pragma once
#include"libs.h"
#include"Shader.h"
namespace gameEngine {
	class FUN_API Camera :public GameObj{
		glm::vec3 camPos;
		glm::mat4 viewMatrix;
		glm::vec3 worldUp;
		glm::vec3 camFront;
		glm::vec3 frontVec;
		float velOfRotation;
	public:
		Camera(glm::vec3 camPosition,const glm::vec3 faceTo = glm::vec3(0.f, 0.f, 0.f), const glm::vec3 upwardDir = glm::vec3(0.f, 1.f, 0.f))
			:camPos(camPosition), camFront(faceTo), worldUp(upwardDir) {
			updateViewMatrix();
			velOfRotation = 0.1f;
			frontVec = faceTo - camPosition;
			this->addKeyEvent(GLFW_KEY_W);
			this->addKeyEvent(GLFW_KEY_A);
			this->addKeyEvent(GLFW_KEY_S);
			this->addKeyEvent(GLFW_KEY_D);
			this->addKeyEvent(GLFW_KEY_Z);
			this->addKeyEvent(GLFW_KEY_X);
		}
		~Camera() {
		}
		void updateViewMatrix() {
			viewMatrix = glm::mat4(1.f);
			viewMatrix = glm::lookAt(camPos, camFront, worldUp);
		}
		void rotateCam(bool left) {
			float angle = velOfRotation;
			if (left) {
				angle = -angle;
			}
			glm::mat4 tempMat(1.f);
			tempMat = glm::rotate(tempMat, glm::radians(angle), worldUp);
			glm::vec4 rotatedCam = tempMat * glm::vec4(frontVec, 0.f);
			frontVec = glm::vec3(rotatedCam.x, rotatedCam.y, rotatedCam.z);
			camFront = camPos + frontVec;
		}
		void onkeyPress(int key) {
			if (key == GLFW_KEY_W) {
				camPos += (frontVec) * 0.01f;
				camFront = camPos + frontVec;
			}
			else if (key == GLFW_KEY_S) {
				camPos -= (frontVec) * 0.01f;
				camFront = camPos + frontVec;
			}
			else if (key == GLFW_KEY_A) {
				rotateCam(false);
			}
			else if (key == GLFW_KEY_D) {
				rotateCam(true);
			}
			else if (key == GLFW_KEY_X) {
				camPos -= (worldUp) * 0.01f;
				camFront = camPos + frontVec;
			}
			else if (key == GLFW_KEY_Z) {
				camPos += (worldUp) * 0.01f;
				camFront = camPos + frontVec;
			}
			
		}

		void sendToShader(std::shared_ptr <Shader> shady) {
			updateViewMatrix();
			shady->setUniformMatrix4fv("viewMatrix", GL_FALSE, viewMatrix);
		}
	};
}