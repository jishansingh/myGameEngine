#pragma once
#include"Shader.h"
#include"Texture.h"
#include"Model.h"
#include"GameObject.h"

namespace gameEngine {
	class FUN_API ObjectRender :public GameObj {
	protected:
		std::shared_ptr <Shader>shady;
	public:
		virtual void updateModelMatrix() {}
		virtual void updateProjMatrix(GLFWwindow* window) {}
		virtual void Draw(const bool instanced=false, const int count = 1) {}
		inline virtual std::shared_ptr <Shader> getShader() { return shady; }
		virtual ~ObjectRender(){}
		inline glm::vec3 getPosition() {
			return glm::vec3(0.f);
		}
		inline glm::vec3 getRotation() {
			return glm::vec3(0.f);
		}
		inline void setShader(std::shared_ptr <Shader> somShader) {
			shady = somShader;
		}
	};


	class FUN_API Quad :public ObjectRender {
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;
		glm::vec3 position;
		glm::vec3 rotation;
		float size = 1.f;
		std::vector<std::shared_ptr<Texture>> textures;
	public:
		Quad(glm::vec3 pos, glm::vec3 rot, float width, float height, std::shared_ptr<Shader> QShad, const float offset = 0.01f);
		Quad(glm::vec3 pos, glm::vec3 rot, float width, float height, const float offset = 0.01f);
		virtual ~Quad() {
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
			glDeleteVertexArrays(1, &vao);
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		void addTexture(std::shared_ptr <Texture> tex) {
			textures.push_back(tex);
		}
		void replaceTex(int i, std::shared_ptr <Texture> tex);
		void updateModelMatrix();
		void updateProjMatrix(GLFWwindow* window);
		void setSize(float inp) {
			size = inp;
		}
		void Draw(const bool instanced = false, const int count = 1);
		void onkeyPress(int key){}
		
	};

	class FUN_API Model :public ObjectRender {
		std::vector<MeshInstance> meshData;
		glm::vec3 position;
		glm::vec3 rotation;
		float size = 1.f;
	public:
		Model(const char* path, glm::vec3 pos, glm::vec3 rot, std::shared_ptr <Shader> shaderM);
		virtual ~Model() {
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		void setSize(float inp) {
			size = inp;
		}
		void updateModelMatrix();
		void updateProjMatrix(GLFWwindow* window);
	};

	class FUN_API instancedRenderer :public ObjectRender {
		std::shared_ptr<ObjectRender> instancedObj;
		std::vector<glm::vec3*> positions;
		std::vector<glm::vec3*> color;
		float size = 1.f;
	public:
		instancedRenderer(std::shared_ptr<ObjectRender> orgObj);
		void updateModelMatrix();
		void updateProjMatrix(GLFWwindow* window);
		void Draw(const bool instanced = false, const int count = 1);
		std::shared_ptr <Shader> getShader() { return instancedObj->getShader(); }

		inline glm::vec3 getPosition();
		inline glm::vec3 getRotation();

		
		void addInstance(glm::vec3 pos, glm::vec3 col);
		void updateDataIndex(int index);
		void setPosition(std::vector<glm::vec3*> pos, std::vector<glm::vec3*> col);

		void sendToShader();
	};
	class FUN_API Cube :public ObjectRender {
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;
		float size;
		glm::vec3 position;
		glm::vec3 rotation;
		std::vector<std::shared_ptr<Texture>> textures;
	public:
		Cube(glm::vec3 pos, glm::vec3 rot, float length, float width, float height, std::shared_ptr<Shader> QShad, const float offset = 0.01f);

		Cube(glm::vec3 pos, glm::vec3 rot, float length, float width, float height, const float offset = 0.01f);
		virtual ~Cube() {
			glDeleteBuffers(1, &vbo);
			//glDeleteBuffers(1, &ibo);
			glDeleteVertexArrays(1, &vao);
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		inline void addTexture(std::shared_ptr <Texture> tex) {
			textures.push_back(tex);
		}
		void replaceTex(int i, std::shared_ptr <Texture> tex);
		void setSize(float ko) {
			size = ko;
		}
		void updateModelMatrix();
		void updateProjMatrix(GLFWwindow* window);

		void Draw(const bool instanced = false, const int count = 1);
		void onkeyPress(int key) {}

	};

}
