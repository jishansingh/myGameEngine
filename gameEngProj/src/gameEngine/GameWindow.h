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
		std::shared_ptr <Quad> window2D;
		std::shared_ptr <Shader> finalShader;
		std::shared_ptr <Camera> winCam;
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

		
	};

	FUN_API GameWindow* initGameWindow(const char* winName = "test window", const int WINDOW_WIDTH = 800, const int WINDOW_HEIGHT = 800);
	FUN_API void deleteWindow();


	FUN_API inline void addToManager(std::shared_ptr <GameObj> somObj);
	FUN_API void addTex(std::shared_ptr <Texture> po);
	FUN_API void addLayer(std::shared_ptr <Layer> som);
	FUN_API void setFinalShader(std::shared_ptr <Shader> shad);
	FUN_API void renderWindow();
	FUN_API void updateWindow();
	FUN_API inline GameWindow* getWindow();
	FUN_API inline GLFWwindow* getGLFWWindow();
	FUN_API void getFrameSize(int& fwidth, int& fheight);
	FUN_API ImGUILayer* getIMGUILayer();

	void createEngine();
}



