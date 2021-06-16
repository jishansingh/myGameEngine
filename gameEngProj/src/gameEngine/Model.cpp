#pragma once

#include"Model.h"
gameEngine::modelLoader* gameEngine::modelLoader::modelLoaderObj;


gameEngine::MeshInstance::MeshInstance(std::shared_ptr<Mesh> mes, std::shared_ptr<Material> som) {
	objMesh = mes;
	meshInsData = new MeshDataInstance();
	meshInsData->objMaterial = som;
}
gameEngine::MeshInstance::MeshInstance(std::shared_ptr<Mesh> mes) {
	objMesh = mes;
	meshInsData = new MeshDataInstance();
}
gameEngine::MeshInstance::MeshInstance() {
	meshInsData = new MeshDataInstance();
}


std::vector<gameEngine::Texture*> gameEngine::modelLoader::loadMaterialTexture(aiMaterial* mat, aiTextureType type, int& cop) {
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

gameEngine::MeshInstance* gameEngine::modelLoader::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<float>vertices;
	std::vector<unsigned int>indexArr;
	std::vector<Texture*>diffTex;
	std::vector<Texture*>specTex;

	for (int i = 0; i < mesh->mNumVertices; i++) {
		//vertex
		vertices.push_back(mesh->mVertices[i].x);
		vertices.push_back(mesh->mVertices[i].y);
		vertices.push_back(mesh->mVertices[i].z);
		//normals
		vertices.push_back(mesh->mNormals[i].x);
		vertices.push_back(mesh->mNormals[i].y);
		vertices.push_back(mesh->mNormals[i].z);

		//texcoord
		glm::vec2 tex_cord;
		if (mesh->mTextureCoords[0]) {
			vertices.push_back(mesh->mTextureCoords[0][i].x);
			vertices.push_back(mesh->mTextureCoords[0][i].y);
		}
		else {
			vertices.push_back(0.f);
			vertices.push_back(0.f);
		}
			
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
	std::shared_ptr<Mesh> mes = std::make_shared<Mesh>(*new Mesh(vertices, indexArr, Mesh::dataDistribution::P3F | Mesh::dataDistribution::N3F | Mesh::dataDistribution::T2F));
	return new MeshInstance( mes,mat);
}


void gameEngine::modelLoader::processNode(aiNode* node, const aiScene* scene, std::vector<MeshInstance*>* meshVec) {
	for (int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		MeshInstance* tempMesh = processMesh(mesh, scene);
		(*meshVec).push_back(tempMesh);
	}
	for (int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene, meshVec);
	}
}
std::vector<gameEngine::MeshInstance*>* gameEngine::modelLoader::loadModel(std::string path) {
	Assimp::Importer importer;
	std::vector<MeshInstance*>* modelMesh = new std::vector<MeshInstance*>();
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags && AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "ASSIMP ERROR:: " << importer.GetErrorString() << std::endl;
		return modelMesh;
	}
	directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene, modelMesh);

	return modelMesh;
}
gameEngine::modelLoader::modelLoader(std::string path) {
	directory = path;
}
void gameEngine::modelLoader::initModelLoader(std::string direcory_name) {
	modelLoaderObj = new modelLoader(direcory_name);
}
std::vector<gameEngine::MeshInstance*>* gameEngine::modelLoader::loadModelFromPath(std::string path) {
	return modelLoaderObj->loadModel(path);
}
/*void Draw(std::shared_ptr <Shader> shader,const bool instanced = false, const int count = 1) {
	for (int i = 0; i < meshes.size(); i++) {
		meshes[i]->Draw(shader, instanced, count);
	}
}*/
gameEngine::modelLoader::~modelLoader() {

}
void gameEngine::modelLoader::deinitModelLoader() {
	delete modelLoaderObj;
}