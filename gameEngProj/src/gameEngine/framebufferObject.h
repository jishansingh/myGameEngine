#pragma once
#include"libs.h"
#include"Core.h"
#include"Texture.h"

namespace gameEngine {
	class FUN_API framebufferObject {
		unsigned int fbo;
		unsigned int rbo;
		std::vector<Texture*> textures;
	public:
		framebufferObject(int noOfColorAttachment,const bool depth = true) {
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			const unsigned int HEIGHT = 1024;
			const unsigned int WIDTH = 1024;
			for (int i = 0; i < noOfColorAttachment; i++) {
				Texture* temp = new Texture(GL_TEXTURE_2D, GL_RGB, GL_RGBA, GL_RGB16F, WIDTH, HEIGHT);
				temp->bindToFrambuffer(i);
				textures.push_back(temp);
			}
			std::vector<GLenum> drawAttach;
			for (int i = 0; i < noOfColorAttachment; i++) {
				drawAttach.push_back(GL_COLOR_ATTACHMENT0 + i);
			}
			glDrawBuffers(drawAttach.size(), drawAttach.data());
			rbo = -1;
			if (depth) {
				glGenRenderbuffers(1, &rbo);
				glBindRenderbuffer(GL_RENDERBUFFER, rbo);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WIDTH, HEIGHT);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
			}


		}
		~framebufferObject() {
			for (int i = 0; i < textures.size(); i++) {
				delete textures[i];
			}
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
	};
}
