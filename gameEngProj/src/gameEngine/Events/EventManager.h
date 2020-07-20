#pragma once
#include"gameEngine/Core.h"
#include"gameEngine/GameObject.h"

namespace gameEngine {
	class FUN_API EventManager {
		std::vector<GameObj*> eventObj;
		std::queue<int>eventQ;
	public:
		EventManager() {
			eventObj = std::vector<GameObj*>();
			eventQ = std::queue<int>();
		}
		void handleKeyboardInput(GLFWwindow* window) {
			//handles A-Z
			int temp = GLFW_KEY_A;
			for (temp; temp < GLFW_KEY_Z + 1; temp++) {
				if (glfwGetKey(window, temp) == GLFW_PRESS)
					eventQ.push(temp);
			}
		}
		void handleKeyboardEvents() {
			while (!eventQ.empty()) {
				int keyPressed = eventQ.front();
				eventQ.pop();
				for (auto somObj : eventObj) {
					somObj->eventManage(keyPressed);
				}
			}
		}
		void addNewObj(GameObj* som) {
			eventObj.push_back(som);
		}
	};
}