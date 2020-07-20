#pragma once
#include"Core.h"
#include"libs.h"
namespace gameEngine {
	class FUN_API Texture {
	private:
		GLuint texture_id;
		int width;
		int height;
		GLint textureUnit;
		GLenum textureType;
	public:
		Texture(std::string filename, GLenum type, GLint texture_unit) {
			stbi_set_flip_vertically_on_load(true);
			this->textureUnit = texture_unit;
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
		GLint getTextureUnit() { return this->textureUnit; }
	};
}

