#pragma once
#include"libs.h"
#include"Mesh.h"
namespace gameEngine {
	struct MeshDataInstance {
		std::shared_ptr<Material> objMaterial;
		glm::mat4* positionMat;
		glm::mat4* scaleMat;
		glm::mat4* rotationMat;
	};

	struct MeshInstance {
		std::shared_ptr<Mesh> objMesh;
		MeshDataInstance meshInsData;
		std::shared_ptr<Shader> shady;
		bool operator==(const MeshInstance& p) const {
			return objMesh == p.objMesh && shady == p.shady;
		}
	};

	class FUN_API modelLoader :public sharedObj{
	private:
		std::string directory;

		int count = 0;
		std::vector<Texture*>loadMaterialTexture(aiMaterial* mat, aiTextureType type, int& cop) {
			std::vector<Texture*>textures;

			for (int i = 0; i < mat->GetTextureCount(type); i++) {
				aiString str;
				mat->GetTexture(type, i, &str);
				Texture* texture = new Texture(directory + "/" + std::string(str.C_Str()), GL_TEXTURE_2D);
				textures.push_back(texture);
			}
			count += mat->GetTextureCount(type);
			//std::cout << textures.size() << std::endl;
			return textures;
		}

		MeshInstance processMesh(aiMesh* mesh, const aiScene* scene) {
			std::vector<Vertex>vertices;
			std::vector<GLuint>indexArr;
			std::vector<Texture*>diffTex;
			std::vector<Texture*>specTex;

			for (int i = 0; i < mesh->mNumVertices; i++) {
				Vertex vert;
				glm::vec3 pos;
				pos.x = mesh->mVertices[i].x;
				pos.y = mesh->mVertices[i].y;
				pos.z = mesh->mVertices[i].z;
				vert.position = pos;

				glm::vec3 norm;
				norm.x = mesh->mNormals[i].x;
				norm.y = mesh->mNormals[i].y;
				norm.z = mesh->mNormals[i].z;
				vert.normal = norm;

				glm::vec2 tex_cord;
				if (mesh->mTextureCoords[0]) {
					tex_cord.x = mesh->mTextureCoords[0][i].x;
					tex_cord.y = mesh->mTextureCoords[0][i].y;
				}
				else
					tex_cord = glm::vec2(0.f);
				vert.texcoord = tex_cord;
				vertices.push_back(vert);
			}

			for (int i = 0; i < mesh->mNumFaces; i++) {
				aiFace& fac = mesh->mFaces[i];
				assert(fac.mNumIndices == 3);
				for (int j = 0; j < fac.mNumIndices; j++) {
					indexArr.push_back(fac.mIndices[j]);
				}
			}
			if (mesh->mMaterialIndex >= 0) {
				aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
				int count = 0;
				diffTex = loadMaterialTexture(material, aiTextureType_DIFFUSE, count);

				specTex = loadMaterialTexture(material, aiTextureType_SPECULAR, count);
			}

			std::shared_ptr<Material> mat = std::make_shared<Material>(*new Material(diffTex.size() > 0 ? diffTex[0] : NULL, specTex.size() > 0 ? specTex[0] : NULL));
			std::shared_ptr<Mesh> mes = std::make_shared<Mesh>(*new Mesh(vertices, indexArr));
			return { mes,mat };
		}


		void processNode(aiNode* node, const aiScene* scene, std::vector<MeshInstance> &meshVec) {
			for (int i = 0; i < node->mNumMeshes; i++) {
				aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
				MeshInstance tempMesh = processMesh(mesh, scene);
				meshVec.push_back(tempMesh);
			}
			for (int i = 0; i < node->mNumChildren; i++) {
				processNode(node->mChildren[i], scene,meshVec);
			}
		}
		std::vector<MeshInstance> loadModel(std::string path) {
			Assimp::Importer importer;
			const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

			if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
				std::cout << "ASSIMP ERROR:: " << importer.GetErrorString() << std::endl;
				return;
			}
			directory = path.substr(0, path.find_last_of('/'));
			std::vector<MeshInstance> modelMesh;
			processNode(scene->mRootNode, scene, modelMesh);

		}
		static modelLoader* modelLoaderObj;
	public:
		modelLoader(std::string path) {
			directory = path;
		}
		static void initModelLoader(std::string direcory_name) {
			modelLoaderObj = new modelLoader(direcory_name);
		}
		static std::vector<MeshInstance>loadModelFromPath(std::string path) {
			return modelLoaderObj->loadModel(path);
		}
		/*void Draw(std::shared_ptr <Shader> shader,const bool instanced = false, const int count = 1) {
			for (int i = 0; i < meshes.size(); i++) {
				meshes[i]->Draw(shader, instanced, count);
			}
		}*/
		~modelLoader() {
			
		}

	};
}

