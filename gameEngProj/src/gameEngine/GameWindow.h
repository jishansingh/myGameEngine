#pragma once
#include"Core.h"
#include"libs.h"
#include"Events/EventManager.h"
#include"Layer.h"
#include"Shader.h"
#include"renderObj.h"
#include"Camera.h"

void framebuffer_resize_callback(GLFWwindow* window, int width, int height);

namespace gameEngine{

	class FUN_API GameWindow {
	public:
		GLFWwindow* window;
		
	//private:
		int glMajorVer = 4;
		int glMinorVer = 4;
		int framebufferheight;
		int framebufferwidth;
		
		
		void initWindow();
		void createWindow(const char* winName, int WINDOW_WIDTH, int WINDOW_HEIGHT);

	//public:
		EventManager* manager;
		std::shared_ptr <Model> window2D;
		std::shared_ptr <Shader> finalShader;
		std::shared_ptr <Camera> winCam;
		std::shared_ptr <Renderer> winRenderer;
		//Camera* winCam;

		std::vector< std::shared_ptr <Texture>>finTex;
		std::vector <std::shared_ptr <Layer>> layerArr;

		GameWindow(const char* winName, const int WINDOW_WIDTH = 800, const int WINDOW_HEIGHT = 800);

		

		static GameWindow* gameWin;
		ImGUILayer* somLay;
		
		virtual ~GameWindow();
		virtual void updateProjMatrix(Shader* shady);

		void initWindowLayer();

		//static inline void addToManager(std::shared_ptr <GameObj> somObj);
		//static void addTex(std::shared_ptr <Texture> po);
		virtual void preRender(){}
		virtual void postRender() { }
		
		void render();
		void update();

		void setFrameSize(int fwidth, int fheight) {
			framebufferwidth = fwidth;
			framebufferheight = fheight;
		}

		static GameWindow* initGameWindow(const char* winName = "test window", const int WINDOW_WIDTH = 800, const int WINDOW_HEIGHT = 800);
		static void deleteWindow();
		static inline void addToManager(std::shared_ptr <GameObj> somObj);
		static void addTex(std::shared_ptr <Texture> po);
		static void addLayer(std::shared_ptr <Layer> som);
		static void setFinalShader(std::shared_ptr <Shader> shad);
		static void renderWindow();
		static void updateWindow();
		static inline GameWindow* getWindow();
		static inline GLFWwindow* getGLFWWindow();
		static void getFrameSize(int& fwidth, int& fheight);
		static void addModel(std::shared_ptr<Model> som);
	};

	
	FUN_API ImGUILayer* getIMGUILayer();

	void createEngine();
}



