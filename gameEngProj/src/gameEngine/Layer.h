#pragma once
#include"Core.h"
#include"libs.h"
#include"DebugWindow.h"

typedef void (*ImGUIFunc)();
namespace gameEngine {
	class GameViewLayer;
	class FUN_API Layer {
	public:
		Layer();
		virtual void onAttach() {
		}
		virtual void onUpdate() {
			
		}
		virtual void renderLayer() {

		}
	};
	
	class IMGUIJob {
	public:
		IMGUIJob(void (*som_func)(void*),void* som) {
			func = som_func;
			parameter = som;
		}
		void (*func)(void*);
		void* parameter;
	};

	class FUN_API ImGUILayer :public Layer{
	public:
		std::vector<IMGUIJob*> menus;
		ImGUILayer();
		void onAttach();
		void onUpdate();
		void renderLayer();
		void endLayer();
		inline void addToMenu(IMGUIJob* somJob) {
			menus.push_back(somJob);
		}
		~ImGUILayer() {
			for (int i = 0; i < menus.size(); i++) {
				delete menus[i];
			}
		}
	};
}
