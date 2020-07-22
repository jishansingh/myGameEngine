#pragma once
#include"libs.h"
#include"Core.h"
#include"Texture.h"

namespace gameEngine {
	class FUN_API framebufferObject {
		unsigned int fbo;
		unsigned int rbo;
	public:
		std::vector<Texture*> textures;
		framebufferObject(int noOfColorAttachment,const bool depth = true) {
			glGenFramebuffers(1, &fbo);
			glBindFramebuffer(GL_FRAMEBUFFER, fbo);
			const unsigned int HEIGHT = 800;
			const unsigned int WIDTH = 800;
			for (int i = 0; i < noOfColorAttachment; i++) {
				bind();
				Texture* temp = new Texture(GL_TEXTURE_2D, GL_RGBA, GL_RGBA16F, GL_FLOAT, WIDTH, HEIGHT);
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
		GLint getFBO() {
			return fbo;
		}
	};
}
