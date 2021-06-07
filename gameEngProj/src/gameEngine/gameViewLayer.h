#include"Layer.h"
#include"framebufferObject.h"
#include"Camera.h"
#include"frameRenderObject.h"
#include"GameWindow.h"
namespace gameEngine {
	class FUN_API GameViewLayer:public Layer {
	public:
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr <frameRenderObject> fro;
		std::shared_ptr <Camera> cam;
		GameViewLayer(GameWindow* win): Layer(win) {
			fbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
			cam = std::make_shared <Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			std::shared_ptr <frameRenderObject> fro = std::make_shared <frameRenderObject>(*new frameRenderObject(fbo, cam));
		}

		virtual void onAttach() {


		}
		virtual void onUpdate() {

		}
	};
}