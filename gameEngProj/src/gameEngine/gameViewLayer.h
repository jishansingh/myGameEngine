#include"Layer.h"
#include"frameRenderObject.h"
#include"CustomShader.h"

static void imguiSize(void* som);

namespace gameEngine {
	
	class FUN_API GameViewLayer:public Layer {
	public:
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr <frameRenderObject> fro;
		std::shared_ptr <Camera> cam;
		float size;
		GameViewLayer(): Layer() {
			fbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
			cam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			fro = std::make_shared <frameRenderObject>(*new frameRenderObject(fbo, cam));
			size = 10.f;
		}
		void setSize(float somSize) {
			size = somSize;
		}
		

		virtual void onAttach() {
			fbo->addAttachment(3);
			fro->initializeAttachments(1);
			std::shared_ptr <gameEngine::Shader> quadShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("quadVertexShader.glsl", "quadFragmentShader.glsl", ""));
			std::shared_ptr <gameEngine::ObjectRender> somLoad = std::make_shared <gameEngine::Quad>(*new gameEngine::Quad(glm::vec3(0.f, -0.5f, 0.f), glm::vec3(90.f, 0.f, 0.f), 0.5f, 0.5f, quadShader));
			std::dynamic_pointer_cast<gameEngine::Quad>(somLoad)->setSize(size);
			//gameEngine::getIMGUILayer()->addToMenu(new IMGUIJob{ &imguiSize,(void*)this });

			ShaderInit sompo;
			std::string vertShader = sompo.getVertShader(ShaderInit::NORM_VERTIN | ShaderInit::TEX_COORDIN);
			std::string fragShader = sompo.getFragShader(ShaderInit::NORM_VERT | ShaderInit::TEX_COORD | ShaderInit::ALBEDO_TEX | ShaderInit::SPECULAR_TEX, ShaderInit::ALBEDO_COLOR | ShaderInit::NORMAL_TEX);
			std::cout << vertShader << std::endl;
			std::cout << fragShader << std::endl;
			std::shared_ptr <gameEngine::Shader> modelShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader(vertShader,fragShader , ""));

			std::shared_ptr <gameEngine::ObjectRender> somLoad1 = std::make_shared <gameEngine::modelLoader>(*new gameEngine::modelLoader("objfile/spaceship.obj", glm::vec3(0.f), glm::vec3(0.f), modelShader));
			std::dynamic_pointer_cast<gameEngine::modelLoader>(somLoad1)->setSize(0.1f);
			std::shared_ptr <gameEngine::Shader> lightShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("sceneLightVertexShader.glsl", "sceneLightFragmentShader.glsl", ""));
			std::vector< std::shared_ptr <gameEngine::Texture>> somtex;

			somtex.push_back(fbo->getTex(0));
			somtex.push_back(fbo->getTex(1));
			somtex.push_back(fbo->getTex(2));
			/*Light* sceneLight = (new Light(somtex, lightShader, true));
			fro->setLighting(sceneLight);
			sceneLight->addNewLight(glm::vec3(1.f, 1.f, -1.f), glm::vec3(0.f));*/

			fro->addRenderObj(somLoad);
			fro->addRenderObj(somLoad1);
			gameEngine::addToManager(cam);
			std::shared_ptr < gameEngine::Shader> finShader = std::make_shared < gameEngine::Shader>(*new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", ""));
			std::shared_ptr<gameEngine::Texture> tex = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture("floor.png", GL_TEXTURE_2D));
			std::dynamic_pointer_cast<gameEngine::Quad>(somLoad)->addTexture(tex);
			gameEngine::addTex(fbo->textures[0]);
			gameEngine::setFinalShader(finShader);
			fbo->check();

		}
		virtual void onUpdate() {
			std::dynamic_pointer_cast<gameEngine::Quad>(fro->renderObj[0])->setSize(size);
		}

		virtual void renderLayer() {
			fbo->bind();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glViewport(0, 0, 1024, 1024);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			fro->render();
			fbo->unBind();
			fro->lightCalc();
		}

		void addObjectToLayer(std::shared_ptr<ObjectRender> somObj) {
			fro->addRenderObj(somObj);
		}
		void setObjectArr(std::vector<std::shared_ptr<ObjectRender>> somObj) {
			fro->setRenderObject(somObj);
		}
	};
	
	
}

static void imguiSize(void* som) {
	ImGui::SliderFloat("float", &((gameEngine::GameViewLayer*)som)->size, 0.0f, 100.0f);
	std::cout << "yes";
}

