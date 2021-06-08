#pragma once
#include"libs.h"
#include"Events/EventManager.h"
#include"Camera.h"
#include"renderObj.h"
#include"frameRenderObject.h"
#include"Light.h"
#include"Layer.h"



void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

namespace gameEngine{

	class FUN_API GameWindow {
	protected:
		GLFWwindow* window;
		EventManager* manager;
		std::shared_ptr <Quad> window2D;
		std::shared_ptr <Shader> finalShader;
		std::shared_ptr <Camera> winCam;
		//Camera* winCam;
		std::vector <std::shared_ptr <Layer>> layerArr;
		std::vector< std::shared_ptr <Texture>>finTex;
		std::vector< std::shared_ptr <frameRenderObject>> frameObj;
	private:
		int glMajorVer = 4;
		int glMinorVer = 4;

		int framebufferheight;
		int framebufferwidth;
		void initWindow();
		void createWindow(const char* winName, int WINDOW_WIDTH, int WINDOW_HEIGHT);
	public:
		ImGUILayer* somLay;
		GameWindow(const char* winName, const int WINDOW_WIDTH, const int WINDOW_HEIGHT );
		virtual ~GameWindow();
		virtual void updateProjMatrix(Shader* shady);
		inline void addFrameObj(std::shared_ptr <frameRenderObject> iop);
		inline void addToManager(std::shared_ptr <GameObj> somObj);
		void addTex(std::shared_ptr <Texture> po);
		void setFinalShader(std::shared_ptr <Shader> shad);
		virtual void preRender(){}
		virtual void postRender() { }
		inline void addLayer(std::shared_ptr <Layer> som) {
			layerArr.push_back(som);
		}
		void render();
		void update();
		GLFWwindow* getWindow() {
			return window;
		}
	};
	void createEngine(GameWindow* som);
}