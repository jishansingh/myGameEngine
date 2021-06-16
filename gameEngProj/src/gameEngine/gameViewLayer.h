#include"Layer.h"
#include"frameRenderObject.h"
#include"CustomShader.h"
#include"Renderer.h"

static void imguiSize(void* som);

namespace gameEngine {
	
	class FUN_API GameViewLayer:public Layer {
	public:
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr <frameRenderObject> fro;
		std::shared_ptr <Camera> cam;
		std::shared_ptr<Renderer> layerRenderer;
		std::vector<std::shared_ptr <gameEngine::Model>> drawModel;
		float size;
		GameViewLayer(): Layer() {
			fbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
			cam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			fro = std::make_shared <frameRenderObject>(*new frameRenderObject(fbo, cam));
			layerRenderer = std::make_shared<Renderer>(*new Renderer());
			size = 100.f;
		}
		void setSize(float somSize) {
			size = somSize;
		}
		

		virtual void onAttach() {
			fbo->addAttachment(3);
			fro->initializeAttachments(1);
			std::shared_ptr<gameEngine::Texture> tex = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture("floor.png", GL_TEXTURE_2D));
			std::shared_ptr < gameEngine::Material> som = std::make_shared < gameEngine::Material>(*new Material(tex));


			ShaderInit sompo;
			std::string vertShader1 = sompo.getVertShader(ShaderInit::TEX_COORDIN);
			std::string fragShader1 = sompo.getFragShader(ShaderInit::TEX_COORD | ShaderInit::ALBEDO_TEX, ShaderInit::ALBEDO_COLOR);
			std::shared_ptr <gameEngine::Shader> modelShader1 = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader(vertShader1, fragShader1, ""));
			std::cout << vertShader1 << std::endl;
			std::cout << fragShader1 << std::endl;


			std::shared_ptr <gameEngine::Shader> quadShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", ""));
			std::shared_ptr <gameEngine::Model> somLoad = std::make_shared <gameEngine::Model>(*new gameEngine::Model(gameEngine::Model::QUAD_MESH,glm::vec3(0.f, 0.f, 0.f), glm::vec3(90.f, 0.f, 0.f), modelShader1));
			(somLoad)->setSize(size);
			somLoad->setMaterial(som);
			//layerRenderer->AddMeshCall(somLoad);
			somLoad->sendToRenderer(layerRenderer);
			//drawModel.push_back(somLoad);
			//std::dynamic_pointer_cast<gameEngine::Quad>(somLoad)->sendToRenderer(layerRenderer);
			//gameEngine::getIMGUILayer()->addToMenu(new IMGUIJob{ &imguiSize,(void*)this });

			std::string vertShader = sompo.getVertShader(ShaderInit::NORM_VERTIN | ShaderInit::TEX_COORDIN);
			std::string fragShader = sompo.getFragShader(ShaderInit::NORM_VERT | ShaderInit::TEX_COORD | ShaderInit::ALBEDO_TEX | ShaderInit::SPECULAR_TEX, ShaderInit::ALBEDO_COLOR | ShaderInit::NORMAL_TEX);
			std::cout << vertShader << std::endl;
			std::cout << fragShader << std::endl;
			std::shared_ptr <gameEngine::Shader> modelShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader(vertShader,fragShader , ""));

			

			std::shared_ptr <gameEngine::Model> somLoad1 = std::make_shared <gameEngine::Model>(*new gameEngine::Model("objfile/spaceship.obj", glm::vec3(0.f,10.f,0.f), glm::vec3(0.f), modelShader));
			(somLoad1)->setSize(1.f);

			std::shared_ptr<gameEngine::Texture> rustex = std::make_shared<gameEngine::Texture>(*new gameEngine::Texture("objfile/rustediron2_basecolor.png", GL_TEXTURE_2D));
			std::shared_ptr < gameEngine::Material> russom = std::make_shared < gameEngine::Material>(*new Material(rustex));

			somLoad1->setMaterial(russom);
			somLoad1->sendToRenderer(layerRenderer);


			std::shared_ptr <gameEngine::Model> somLoad2 = std::make_shared <gameEngine::Model>(*new gameEngine::Model("objfile/nanosuit/nanosuit.obj", glm::vec3(20.f, 0.f, 0.f), glm::vec3(0.f), modelShader));
			(somLoad2)->setSize(1.f);

			somLoad2->sendToRenderer(layerRenderer);


			//std::dynamic_pointer_cast<gameEngine::Model>(somLoad1)->sendToRenderer(layerRenderer);
			std::shared_ptr <gameEngine::Shader> lightShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("sceneLightVertexShader.glsl", "sceneLightFragmentShader.glsl", ""));
			std::vector< std::shared_ptr <gameEngine::Texture>> somtex;
			drawModel.push_back(somLoad1);
			somtex.push_back(fbo->getTex(0));
			somtex.push_back(fbo->getTex(1));
			somtex.push_back(fbo->getTex(2));
			/*Light* sceneLight = (new Light(somtex, lightShader, true));
			fro->setLighting(sceneLight);
			sceneLight->addNewLight(glm::vec3(1.f, 1.f, -1.f), glm::vec3(0.f));*/

			//fro->addRenderObj(somLoad);
			//fro->addRenderObj(somLoad1);
			gameEngine::GameWindow::addToManager(cam);
			std::shared_ptr < gameEngine::Shader> finShader = std::make_shared < gameEngine::Shader>(*new gameEngine::Shader("finalVertexShader.glsl", "finalFragmentShader.glsl", ""));
			
			/*std::shared_ptr <gameEngine::Model> somLoad2 = std::make_shared<gameEngine::Model>(*new Model(*somLoad1.get()));
			somLoad2->setShader(finShader);
			(somLoad2)->setMaterial(som);
			GameWindow::addModel(somLoad2);*/
			gameEngine::GameWindow::addTex(fbo->getTex(0));
			gameEngine::GameWindow::setFinalShader(finShader);
			fbo->check();

		}
		void updateProjectionMat(std::shared_ptr <Shader> shady) {
			int framebufferwidth = 800;
			int framebufferheight = 800;
			fbo->bind();
			gameEngine::GameWindow::getFrameSize(framebufferwidth, framebufferheight);

			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 53.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);

			cam->updateViewMatrix();
			cam->sendToShader(shady);
		}
		virtual void onUpdate() {
			//std::dynamic_pointer_cast<gameEngine::Quad>(fro->renderObj[0])->setSize(size);
		}

		virtual void renderLayer() {
			fbo->bind();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
			layerRenderer->Draw(cam);
			fbo->unBind();
			//fro->lightCalc();
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

