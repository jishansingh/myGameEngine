#pragma once
#include"renderObj.h"
#include"Renderer.h"


gameEngine::Model::Model(const char* path, glm::vec3 pos, glm::vec3 rot, std::shared_ptr <Shader> shaderM,int cusSize) :
	position(pos), rotation(rot),size(cusSize) {
	shady = shaderM;
	meshData = modelLoader::loadModelFromPath(path);
	for (int i = 0; i < meshData->size(); i++) {
		(*meshData)[i]->shady = shaderM;
		glm::mat4* modelMatrix = new glm::mat4(1.f);
		*modelMatrix = glm::translate(*modelMatrix, position);
		(*meshData)[i]->meshInsData->positionMat = modelMatrix;
		modelMatrix = new glm::mat4(1.f);
		*modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
		*modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
		*modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
		(*meshData)[i]->meshInsData->rotationMat = modelMatrix;
		modelMatrix = new glm::mat4(1.f);
		*modelMatrix = glm::scale(*modelMatrix, glm::vec3(size));
		(*meshData)[i]->meshInsData->scaleMat = modelMatrix;
		if (!(*meshData)[i]->meshInsData->objMaterial) {
			(*meshData)[i]->meshInsData->objMaterial = std::make_shared<Material>(*new Material());
		}
	}
	
}

gameEngine::Model::Model(int custMesh, glm::vec3 pos, glm::vec3 rot, std::shared_ptr <Shader> shaderM, glm::vec3 cusSize) :
	position(pos), rotation(rot), size(cusSize) {
	shady = shaderM;
	meshData = new std::vector<MeshInstance*>();
	MeshInstance* somp = new MeshInstance();
	MeshInstance* temp = somp;
	if (custMesh & CUBE_MESH) {
		temp->objMesh = std::make_shared<Mesh>(*CustomMesh::getCustomCube());
	}
	else {
		temp->objMesh = std::make_shared<Mesh>(*CustomMesh::getCustomQuad());
	}
	temp->shady = shady;
	glm::mat4* modelMatrix = new glm::mat4(1.f);
	*modelMatrix = glm::translate(*modelMatrix, position);
	temp->meshInsData->positionMat = modelMatrix;
	modelMatrix = new glm::mat4(1.f);
	*modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
	*modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
	*modelMatrix = glm::rotate(*modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
	temp->meshInsData->rotationMat = modelMatrix;
	modelMatrix = new glm::mat4(1.f);
	*modelMatrix = glm::scale(*modelMatrix, size);
	temp->meshInsData->scaleMat = modelMatrix;

	if (temp->meshInsData->objMaterial) {}
	else {
		temp->meshInsData->objMaterial = std::make_shared<Material>(*new Material());
	}

	meshData->push_back(temp);
}

void gameEngine::Model::setShader(std::shared_ptr<Shader> som) {
	for (int i = 0; i < meshData->size(); i++) {
		(*meshData)[i]->shady = som;
	}
}


void gameEngine::Model::sendToRenderer(std::shared_ptr<Renderer> som) {
	som->AddMeshCall(meshData);
}

void gameEngine::Model::updateModelMatrix() {
	glm::mat4 modelMatrix(1.f);
	modelMatrix = glm::translate(modelMatrix, position);
	
	
	modelMatrix = glm::scale(modelMatrix, glm::vec3(size));
	shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
}
void gameEngine::Model::updateProjMatrix(GLFWwindow* window) {
	int framebufferwidth = 800;
	int framebufferheight = 800;
	//glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
	glm::mat4 projMatrix(1.f);
	float nearPlane = 0.1f;
	float farPlane = 100.f;
	float fov = 45.f;
	projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
	shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
}

inline void gameEngine::Model::setSize(int inp) {
	size = glm::vec3(inp);
	glm::mat4 som(1.f);
	som = glm::scale(som, size);
	for (int i = 0; i < meshData->size(); i++) {
		*(*meshData)[i]->meshInsData->scaleMat = som;
	}
}
inline void gameEngine::Model::setSize(glm::vec3 inp) {
	size = inp;
	glm::mat4 som(1.f);
	som = glm::scale(som, size);
	for (int i = 0; i < meshData->size(); i++) {
		*(*meshData)[i]->meshInsData->scaleMat = som;
	}
}
