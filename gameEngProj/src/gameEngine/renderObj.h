#pragma once
#include"Shader.h"
#include"Texture.h"
#include"Model.h"

namespace gameEngine {
	class FUN_API ObjectRender :public GameObj {
	public:
		virtual void updateModelMatrix() {}
		virtual void updateProjMatrix(GLFWwindow* window) {}
		virtual void Draw() {}
		virtual Shader* getShader() { return NULL; }
		virtual ~ObjectRender(){}
	};


	class FUN_API Quad :public ObjectRender {
		Shader* shady;
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;
		glm::vec3 position;
		glm::vec3 rotation;
		std::vector<Texture*> textures;
	public:
		Quad(glm::vec3 pos,glm::vec3 rot,float width, float height,Shader* QShad ,const float offset=0.01f) {
			shady = QShad;
			position = pos;
			rotation = rot;
			float farWid = 2 * (width - offset);
			float vertices_box[16]{
				0.f,2 * (height - offset),0.f,1.f,
				0.f,0.f,0.f,0.f,
				2 * (width - offset),0.f,1.f,0.f,
				2 * (width - offset),2 * (height - offset),1.f,1.f
			};
			unsigned int noOfVertices = sizeof(vertices_box) / (4 * sizeof(float));
			GLuint indVert[] = {
				2,1,0,
				3,2,0
			};
			glBindVertexArray(0);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, noOfVertices * 4 * sizeof(float), &vertices_box[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indVert, GL_STATIC_DRAW);
		}
		void addTexture(Texture* tex) {
			textures.push_back(tex);
		}
		void updateModelMatrix() {
			glm::mat4 modelMatrix(1.f);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
			shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		}
		void updateProjMatrix(GLFWwindow* window) {
			int framebufferwidth;
			int framebufferheight;
			glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 45.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}

		void Draw() {
			shady->Use();

			for (int i = 0; i < textures.size();i++) {
				textures[i]->bind();
				std::string temp = "texture" + std::to_string(i);
				shady->setUniform1i(temp.c_str(), textures[i]->getTextureUnit());
			}
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		void onkeyPress(int key){}
		Shader* getShader() {
			return shady;
		}
		~Quad() {
			for (int i = 0; i < textures.size(); i++) {
				delete textures[i];
			}
			delete shady;
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
			glDeleteVertexArrays(1, &vao);
		}
	};

	class FUN_API modelLoader :public ObjectRender {
		Model* model;
		Shader* shady;
		glm::vec3 position;
		glm::vec3 rotation;
	public:
		modelLoader(const char* path, glm::vec3 pos, glm::vec3 rot,Shader* shaderM) :
			position(pos), rotation(rot) {
			shady = shaderM;
			model = new Model(path);
		}
		~modelLoader() {
			delete model;
			delete shady;
		}
		Shader* getShader() {
			return shady;
		}
		void updateModelMatrix() {
			glm::mat4 modelMatrix(1.f);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
			shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		}
		void updateProjMatrix(GLFWwindow* window) {
			int framebufferwidth;
			int framebufferheight;
			glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 45.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}
		void Draw() {
			model->Draw(shady);
		}
	};
}
