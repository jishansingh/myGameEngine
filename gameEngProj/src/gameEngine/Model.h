#pragma once
#include"libs.h"
#include"CustomMesh.h"
#include"Material.h"
namespace gameEngine {
	class FUN_API MeshDataInstance {
	public:
		MeshDataInstance() {}
		std::shared_ptr<Material> objMaterial;
		glm::mat4* positionMat;
		glm::mat4* scaleMat;
		glm::mat4* rotationMat;
	};

	class FUN_API MeshInstance {
	public:
		std::shared_ptr<Mesh> objMesh;
		MeshDataInstance* meshInsData;
		std::shared_ptr<Shader> shady;

		MeshInstance(std::shared_ptr<Mesh> mes, std::shared_ptr<Material> som);
		MeshInstance(std::shared_ptr<Mesh> mes);
		MeshInstance();

		bool operator==(const MeshInstance& p) const {
			return objMesh.get() == p.objMesh.get() && shady.get() == p.shady.get();
		}
		bool operator==(MeshInstance& p) const {
			return objMesh.get() == p.objMesh.get() && shady.get() == p.shady.get();
		}
	};

	class FUN_API modelLoader :public sharedObj{
	private:
		std::string directory;

		int count = 0;
		std::vector<Texture*>loadMaterialTexture(aiMaterial* mat, aiTextureType type, int& cop);

		MeshInstance* processMesh(aiMesh* mesh, const aiScene* scene);


		void processNode(aiNode* node, const aiScene* scene, std::vector<MeshInstance*>* meshVec);
		std::vector<MeshInstance*>* loadModel(std::string path);
		static modelLoader* modelLoaderObj;
	public:
		modelLoader(std::string path);
		static void initModelLoader(std::string direcory_name);
		static std::vector<MeshInstance*>* loadModelFromPath(std::string path);
		/*void Draw(std::shared_ptr <Shader> shader,const bool instanced = false, const int count = 1) {
			for (int i = 0; i < meshes.size(); i++) {
				meshes[i]->Draw(shader, instanced, count);
			}
		}*/
		static void deinitModelLoader();
		~modelLoader();

	};
}
