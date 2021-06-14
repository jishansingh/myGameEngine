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
		GLenum textureType;
	public:
		Texture(GLenum type, GLint inFormat, GLint outFormat, GLenum storageFormat, int wid, int high,void* data=NULL);
		Texture(std::string filename, GLenum type);
		~Texture();
		void unbind();
		GLuint getID() const;
		void bind(int textureUnit);
		void bindToFrambuffer(int i);
		void bindAsDepthBuffer();
	};
}

