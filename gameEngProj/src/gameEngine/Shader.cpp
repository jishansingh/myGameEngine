#pragma once

#include"Shader.h"
#include"CustomShader.h"
std::string gameEngine::Shader::loadShaderSource(char* filename) {
	std::string shaderSource = "";
	std::string temp = "";
	std::ifstream fil_index;
	fil_index.open(filename);
	if (fil_index.is_open()) {
		while (std::getline(fil_index, temp))
			shaderSource += temp + "\n";
	}
	else {
		std::cout << "UNABLE TO OPEN FILE " << filename << std::endl;
		return "";
	}
	fil_index.close();
	return shaderSource;
}

GLuint gameEngine::Shader::loadShader(GLuint type, std::string vertexSource) {
	GLuint shader_id = glCreateShader(type);
	const GLchar* vertexSrc = vertexSource.c_str();
	glShaderSource(shader_id, 1, &vertexSrc, NULL);
	glCompileShader(shader_id);

	char infoLog[512];
	GLint success;
	glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
		std::cout << infoLog << std::endl;
		return false;
	}

	//attach to prog_id

	return shader_id;
}
void gameEngine::Shader::linkProgram(GLuint vertexShader, GLuint fragmentShader, GLuint geometryShader) {
	this->prog_id = glCreateProgram();
	glAttachShader(this->prog_id, vertexShader);
	glAttachShader(this->prog_id, fragmentShader);
	if (geometryShader) {
		glAttachShader(this->prog_id, geometryShader);
	}
	glLinkProgram(this->prog_id);
	char infoLog[512];
	GLint success;
	glGetShaderiv(this->prog_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->prog_id, 512, NULL, infoLog);
		std::cout << "ERROR: LOADING SHADER COULD NOT LINK PROGRAM" << std::endl;
		std::cout << infoLog << std::endl;
	}

}

gameEngine::Shader::Shader(const char* vertexFile, const char* fragmentFile, const char* geometryFile) {
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	GLuint geometryShader = 0;

	vertexShader = loadShader(GL_VERTEX_SHADER, this->loadShaderSource((char*)vertexFile));
	fragmentShader = loadShader(GL_FRAGMENT_SHADER, this->loadShaderSource((char*)fragmentFile));
	if (geometryFile&&*geometryFile != '\0') {
		geometryShader = loadShader(GL_GEOMETRY_SHADER, this->loadShaderSource((char*)geometryFile));
	}
	linkProgram(vertexShader, fragmentShader, geometryShader);
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShader) {
		glDeleteShader(geometryShader);
	}
}
gameEngine::Shader::Shader(std::string vertexSource, std::string fragSource, std::string geomSource) {
	GLuint vertexShader = 0;
	GLuint fragmentShader = 0;
	GLuint geometryShader = 0;

	vertexShader = loadShader(GL_VERTEX_SHADER, vertexSource);
	fragmentShader = loadShader(GL_FRAGMENT_SHADER,fragSource);
	if (geomSource != "") {
		geometryShader = loadShader(GL_GEOMETRY_SHADER, geomSource);
	}
	linkProgram(vertexShader, fragmentShader, geometryShader);
	glUseProgram(0);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	if (geometryShader) {
		glDeleteShader(geometryShader);
	}
}
gameEngine::Shader::~Shader() {
	for (int i = 0; i < shaderUniformArr.size(); i++) {
		delete shaderUniformArr[i];
	}
	glDeleteProgram(this->prog_id);
}
inline void gameEngine::Shader::Use() {
	glUseProgram(this->prog_id);
}
inline void gameEngine::Shader::unUse() {
	glUseProgram(0);
}
void gameEngine::Shader::setUniformMatrix4fv(const char* un_name, GLboolean normalize, glm::mat4& data) {
	glUniformMatrix4fv(glGetUniformLocation(this->prog_id, un_name), 1, normalize, glm::value_ptr(data));
}
void gameEngine::Shader::setUniform3f(const char* un_name, GLboolean normalize, glm::vec3& data) {
	glUniform3fv(glGetUniformLocation(this->prog_id, un_name), 1, glm::value_ptr(data));
}
void gameEngine::Shader::setUniform1i(const char* un_name, int data) {
	GLint loc = glGetUniformLocation(this->prog_id, un_name);
	if (loc < 0) {
		//std::cout << "warning setting uniform " << un_name << " " << data << std::endl;
	}
	glUniform1i(loc, data);
}
void gameEngine::Shader::setUniform2f(const char* un_name, glm::vec2& data) {
	GLint loc = glGetUniformLocation(this->prog_id, un_name);
	if (loc < 0) {
		//std::cout << "warning setting uniform " << un_name << " " << data << std::endl;
	}
	glUniform2f(loc, data.x, data.y);
}
void gameEngine::Shader::setUniform1f(const char* un_name, float data) {
	glUniform1f(glGetUniformLocation(this->prog_id, un_name), data);
}
void gameEngine::Shader::updateUniform() {
	for (shaderUniform* som : shaderUniformArr) {
		som->bind(this);
	}
}
void gameEngine::Shader::setUniform(const char* un_name, void* data) {
	for (shaderUniform* som : shaderUniformArr) {
		if (som->name == un_name) {
			som->setVal(data);
			break;
		}
	}
}
void gameEngine::Shader::addUniform(std::vector<shaderUniform*> som) {
	shaderUniformArr = som;
}
inline GLuint gameEngine::Shader::getID() const { return this->prog_id; }


