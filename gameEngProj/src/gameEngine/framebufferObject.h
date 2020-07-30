#pragma once
#include"libs.h"
#include"Core.h"
#include"Texture.h"

namespace gameEngine {
	class FUN_API framebufferObject :public sharedObj {
		unsigned int fbo;
		unsigned int rbo;
	public:
		std::vector<std::shared_ptr <Texture>> textures;
		std::shared_ptr <Texture> depthTex;
		framebufferObject(int noOfColorAttachment,const bool depth = true) {
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			const unsigned int HEIGHT = 1024;
			const unsigned int WIDTH = 1024;
			for (int i = 0; i < noOfColorAttachment; i++) {
				bind();
				Texture* temp = new Texture(GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_FLOAT, WIDTH, HEIGHT);
				temp->bindToFrambuffer(i);
				textures.push_back(std::make_shared<Texture>(*temp));
				temp->unbind();
			}
			std::vector<GLenum> drawAttach;
			for (int i = 0; i < noOfColorAttachment; i++) {
				drawAttach.push_back(GL_COLOR_ATTACHMENT0 + i);
			}
			//glDrawBuffer(GL_COLOR_ATTACHMENT0);
			
			glDrawBuffers(drawAttach.size(), drawAttach.data());
			rbo = -1;
			depthTex = NULL;
			if (!depth) {
				glGenRenderbuffers(1, &rbo);
				glBindRenderbuffer(GL_RENDERBUFFER, rbo);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			}
			else {
				bind();
				Texture* tempTex = new Texture(GL_TEXTURE_2D, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT, GL_FLOAT, WIDTH, HEIGHT);
				depthTex = std::make_shared<Texture>(*tempTex);
				depthTex->bindAsDepthBuffer();
				//depthTex->unbind();
			}
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		}
		~framebufferObject() {
			if (rbo != -1) {
				glDeleteRenderbuffers(1, &rbo);
			}
			glDeleteFramebuffers(1, &fbo);
		}
		void bind() {
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		}
		void unBind() {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
		unsigned int getFBO() {
			return fbo;
		}
	};
}
