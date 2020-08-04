#pragma once
#include"libs.h"
#include"frameRenderObject.h"
namespace gameEngine {
	

	class FUN_API texOperation {
		static std::shared_ptr<gameEngine::Camera> simpleCam;
		static std::shared_ptr<gameEngine::frameRenderObject> fro;
	public:
		static std::shared_ptr<frameRenderObject> createSimpleFrame(int noOfAttachment) {
			std::shared_ptr<framebufferObject> tempfbo = std::make_shared<framebufferObject>(*new framebufferObject(noOfAttachment));
			std::shared_ptr<frameRenderObject> sik = std::make_shared<frameRenderObject>(*new frameRenderObject(tempfbo, simpleCam));
			return sik;
		}
		static std::shared_ptr<frameRenderObject> createSimpleFrame(std::vector<std::shared_ptr<Texture>> attach) {
			std::shared_ptr<framebufferObject> tempfbo = std::make_shared<framebufferObject>(*new framebufferObject(attach));
			std::shared_ptr<frameRenderObject> sik = std::make_shared<frameRenderObject>(*new frameRenderObject(tempfbo, simpleCam));
			return sik;
		}
		static void copyTextureDeep(std::shared_ptr<frameRenderObject> fro, std::shared_ptr<Texture> tex) {
			std::shared_ptr<frameRenderObject> spl = createSimpleFrame(1);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, fro->getFBO()->getFBO());
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, spl->getFBO()->getFBO());
			glBlitFramebuffer(0, 0, 0, 0, 1024, 1024, 1024, 1024, GL_COLOR_BUFFER_BIT, GL_LINEAR);
			tex = spl->getFBO()->getTex(0);
		}
		static void copyTextureNoTex(std::shared_ptr<frameRenderObject> som, std::shared_ptr<Texture> tex) {
			fro->getFBO()->addTexture(tex, 0);
			glBindFramebuffer(GL_READ_FRAMEBUFFER, som->getFBO()->getFBO());
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, fro->getFBO()->getFBO());
			glBlitFramebuffer(0, 0, 0, 0, 1024, 1024, 1024, 1024, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		}

		static void initCamera() {
			simpleCam = std::make_shared<Camera>(*new Camera(glm::vec3(0.f, 0.f, 1.f)));
			std::shared_ptr<framebufferObject> tempfbo = std::make_shared<framebufferObject>(*new framebufferObject());
			fro = std::make_shared<frameRenderObject>(*new frameRenderObject(tempfbo, simpleCam));
		}

	};

}
std::shared_ptr<gameEngine::Camera> gameEngine::texOperation::simpleCam;
std::shared_ptr<gameEngine::frameRenderObject> gameEngine::texOperation::fro;