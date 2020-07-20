#pragma once
#include<MainHeader.h>
#include"Events.h"
namespace gameEngine {
	class FUN_API KeyboardEvent :public BaseEvent {
	public:
		KeyboardEvent() {
		}
	};
	class FUN_API keyPressed :public KeyboardEvent {
		int keyNum;
	public:
		keyPressed(int keyNumber):keyNum(keyNumber) {}
	};
}

