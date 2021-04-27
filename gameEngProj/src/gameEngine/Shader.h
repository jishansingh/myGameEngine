#pragma once

#include"libs.h"
#include"sharedObj.h"

namespace gameEngine {
	class FUN_API Shader :public sharedObj {
	private:
		GLuint prog_id;
		//private functions

		std::string loadShaderSource(char* filename);

		GLuint loadShader(GLuint type, std::string vertexSource);
		void linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader = 0);
	public:
		Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile);
		Shader(std::string vertexSource, std::string fragSource, std::string geomSource);
		~Shader();
		inline void Use();
		inline void unUse();
		void setUniformMatrix4fv(const char* un_name, GLboolean normalize, glm::mat4& data);
		void setUniform3f(const char* un_name, GLboolean normalize, glm::vec3& data);
		void setUniform1i(const char* un_name, int data);
		void setUniform2f(const char* un_name, glm::vec2& data);
		void setUniform1f(const char* un_name, float data);
		inline GLuint getID() const;


	};
}

