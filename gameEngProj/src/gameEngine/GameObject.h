#pragma once
#include"libs.h"
namespace gameEngine {
	class FUN_API GameObj {
	protected:
		enum {
			KEY_A=0,
			KEY_B,
			KEY_C,
			KEY_D,
			KEY_E,
			KEY_F,
			KEY_G,
			KEY_H,
			KEY_I,
			KEY_J,
			KEY_K,
			KEY_L,
			KEY_M,
			KEY_N,
			KEY_O,
			KEY_P,
			KEY_Q,
			KEY_R,
			KEY_S,
			KEY_T,
			KEY_U,
			KEY_V,
			KEY_W,
			KEY_X,
			KEY_Y,
			KEY_Z
		};
		std::vector<int>keysEvents;
	public:
		GameObj(){}
		virtual ~GameObj() {
		}
		virtual void onkeyPress(int keyNum){}
		void addKeyEvent(int key) {
			keysEvents.push_back(key);
		}
		void eventManage(int key) {
			if (std::find(keysEvents.begin(), keysEvents.end(), key) != keysEvents.end()) {
				this->onkeyPress(key);
			}
		}
	};
}


