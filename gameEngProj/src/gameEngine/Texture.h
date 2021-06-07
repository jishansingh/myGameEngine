#pragma once
#include"Core.h"
#include"libs.h"
#include"sharedObj.h"
namespace gameEngine {
	class FUN_API Texture :public sharedObj {
	private:
		GLuint texture_id;
		int width;
		int height;
		GLint textureUnit;
		GLenum textureType;
	public:
		static GLint totalTexUnit;
		Texture(GLenum type, GLint inFormat, GLint outFormat, GLenum storageFormat, int wid, int high);
		Texture(std::string filename, GLenum type);
		~Texture();
		void unbind();
		GLuint getID() const;
		void bind();
		void bindToFrambuffer(int i);
		void bindAsDepthBuffer();
		GLint getTextureUnit();
	};
}

