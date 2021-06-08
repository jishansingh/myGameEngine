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
			cam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			fro = std::make_shared <frameRenderObject>(*new frameRenderObject(fbo, cam));
		}

		virtual void onAttach() {
			fbo->addAttachment(3);
			fro->initializeAttachments(1);

			std::shared_ptr <gameEngine::Shader> quadShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("quadVertexShader.glsl", "quadFragmentShader.glsl", ""));
			std::shared_ptr <gameEngine::ObjectRender> somLoad = std::make_shared <gameEngine::Quad>(*new gameEngine::Quad(glm::vec3(0.f, -0.5f, 0.f), glm::vec3(90.f, 0.f, 0.f), 0.5f, 0.5f, quadShader));
			std::dynamic_pointer_cast<gameEngine::Quad>(somLoad)->setSize(100.f);
			std::shared_ptr <gameEngine::Shader> lightShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("sceneLightVertexShader.glsl", "sceneLightFragmentShader.glsl", ""));
			std::vector< std::shared_ptr <gameEngine::Texture>> somtex;

			somtex.push_back(fbo->getTex(0));
			somtex.push_back(fbo->getTex(1));
			somtex.push_back(fbo->getTex(2));
			/*Light* sceneLight = (new Light(somtex, lightShader, true));
			fro->setLighting(sceneLight);
			sceneLight->addNewLight(glm::vec3(1.f, 1.f, -1.f), glm::vec3(0.f));*/

			fro->addRenderObj(somLoad);
			window->addToManager(cam);
			std::shared_ptr < gameEngine::Shader> finShader = std::make_shared < gameEngine::Shader>(*new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", ""));
			std::shared_ptr<gameEngine::Texture> tex = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture("floor.png", GL_TEXTURE_2D));
			std::dynamic_pointer_cast<gameEngine::Quad>(somLoad)->addTexture(tex);
			window->addTex(fbo->textures[0]);
			window->setFinalShader(finShader);
			fbo->check();

		}
		virtual void onUpdate() {

		}

		virtual void renderLayer() {
			fbo->bind();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, 1024, 1024);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			fro->render(window->getWindow());
			fbo->unBind();
			fro->lightCalc(window->getWindow());
		}

		void addObjectToLayer(std::shared_ptr<ObjectRender> somObj) {
			fro->addRenderObj(somObj);
		}
		void setObjectArr(std::vector<std::shared_ptr<ObjectRender>> somObj) {
			fro->setRenderObject(somObj);
		}

	};
}