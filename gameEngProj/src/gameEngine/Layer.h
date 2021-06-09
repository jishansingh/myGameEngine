#pragma once
#include"Core.h"
#include"libs.h"
#include"DebugWindow.h"

typedef void (*ImGUIFunc)();
namespace gameEngine {

	class GameWindow;
	class FUN_API Layer {
	public:
		GameWindow* window;
		Layer(GameWindow* win);
		virtual void onAttach() {
		}
		virtual void onUpdate() {
			
		}
		virtual void renderLayer() {

		}
	};
	
	
	class FUN_API ImGUILayer :public Layer{
	public:
		std::vector<void (*)()> menus;
		ImGUILayer(GameWindow* win);
		void onAttach();
		void onUpdate();
		void renderLayer();
		void endLayer();
		inline void addToMenu(void (*func)() ) {
			menus.push_back(func);
		}
	};
}
