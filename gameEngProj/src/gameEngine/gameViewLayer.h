#include"Layer.h"
#include"frameRenderObject.h"
#include"Renderer.h"



namespace gameEngine {
	void imguiSize(void* som);
	class FUN_API GameViewLayer:public Layer {
	public:
		std::shared_ptr<framebufferObject> fbo;
		std::shared_ptr <Camera> cam;
		std::shared_ptr<Renderer> layerRenderer;
		std::vector<std::shared_ptr <gameEngine::Model>> drawModel;

		
		int layerOutput;

		float size;
		GameViewLayer(int state): Layer() {
			layerOutput = state;
			fbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
			cam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			layerRenderer = std::make_shared<Renderer>(*new Renderer(state));
			int count = 0;
			for (int i = 0; i < 4; i++) {
				if (state & (1 << i)) {
					count++;
				}
			}
			fbo->addAttachment(count);
			size = 100.f;
		}
		void setSize(float somSize) {
			size = somSize;
		}
		void setLayerOutput(int layOutput) {
			layerOutput = layOutput;
		}

		virtual void onAttach();
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
		void sendToRenderer(std::shared_ptr <gameEngine::Model>& modelObj) {
			modelObj->sendToRenderer(layerRenderer);
		}
	};
	
}



