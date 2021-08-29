#pragma once
#include"Model.h"

namespace gameEngine {
	class Renderer;
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


	class FUN_API Model :public ObjectRender {
		std::vector<MeshInstance*> * meshData;
		glm::vec3 position;
		glm::vec3 rotation;
		glm::vec3 size;
	public:
		enum customObj {
			CUBE_MESH,
			QUAD_MESH
		};

		Model(const char* path, glm::vec3 pos, glm::vec3 rot, std::shared_ptr <Shader> shaderM=NULL, int cusSize = 1);
		Model(int type, glm::vec3 pos, glm::vec3 rot, std::shared_ptr <Shader> shaderM=NULL, glm::vec3 cusSize = glm::vec3(1.f));
		virtual ~Model() {
			delete meshData;
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		inline void setSize(glm::vec3 inp);
		void setShader(std::shared_ptr<Shader> som);
		inline void setSize(int inp);
		inline void setMaterial(int index,std::shared_ptr<Material> mat) {
			(*meshData)[index]->meshInsData->objMaterial = mat;
		}
		inline void setMaterial(std::shared_ptr<Material> mat) {
			for (int i = 0; i < meshData->size(); i++) {
				(*meshData)[i]->meshInsData->objMaterial = mat;
			}
		}
		void sendToRenderer(std::shared_ptr<Renderer> som);
		void updateModelMatrix();
		void updateProjMatrix(GLFWwindow* window);
	};



}
