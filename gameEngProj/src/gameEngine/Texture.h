#pragma once
#include"Core.h"
#include"libs.h"
namespace gameEngine {
	class FUN_API Texture :public sharedObj {
	private:
		static GLint totalTexUnit;
		GLuint texture_id;
		int width;
		int height;
		GLint textureUnit;
		GLenum textureType;
	public:
		Texture(GLenum type,GLint inFormat,GLint outFormat,GLenum storageFormat,int wid,int high) {
			this->width = wid;
			this->height = high;
			this->textureType = type;
			this->textureUnit = totalTexUnit;
			totalTexUnit++;
			glGenTextures(1, &texture_id);
			glBindTexture(GL_TEXTURE_2D, texture_id);

			glTexImage2D(GL_TEXTURE_2D, 0, inFormat, width, height, 0, outFormat, storageFormat, NULL);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			unbind();
			
		}
		Texture(std::string filename, GLenum type) {
			stbi_set_flip_vertically_on_load(true);
			this->textureUnit = totalTexUnit;
			totalTexUnit++;
			this->textureType = type;
			unsigned char* image = SOIL_load_image(filename.c_str(), &this->width, &this->height, NULL, SOIL_LOAD_RGBA);

			glGenTextures(1, &texture_id);
			glBindTexture(type, texture_id);
			/*
			glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR);*/
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);


			if (image) {
				glTexImage2D(type, 0, GL_SRGB, this->width, this->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
				glGenerateMipmap(type);
			}
			else {
				std::cout << "ERROR::TEXTURE LOADING FAILED" << filename << "\n";
			}
			unbind();
			SOIL_free_image_data(image);

		}
		~Texture() {
			glDeleteTextures(1, &this->texture_id);
				
		}
		void unbind() {
			glActiveTexture(0);
			glBindTexture(this->textureType, 0);
		}
		GLuint getID() const {
			return this->texture_id;
		}
		void bind() {
			glActiveTexture(GL_TEXTURE0 + this->textureUnit);
			glBindTexture(this->textureType, this->texture_id);
		}
		void bindToFrambuffer(int i) {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, texture_id, 0);
		}
		void bindAsDepthBuffer() {
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture_id, 0);
		}
		GLint getTextureUnit() { return this->textureUnit; }
	};
}

