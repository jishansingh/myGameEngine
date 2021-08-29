#pragma once
#include"libs.h"
#include"Model.h"
#include"Camera.h"
namespace gameEngine {
	
	class Renderer {
		std::vector< MeshInstance*>meshArr;
		std::vector< std::vector<MeshDataInstance*>> instanceArr;
	public:
		Renderer(){}
		int checkInList(MeshInstance* somP) {
			return -1;
			/*for (int i = 0; i < meshArr.size(); i++) {
				if (meshArr[i] == somP) {
					return i;
				}
			}*/
			return -1;
		}
		void AddMeshCall(MeshInstance* som) {
			int index = checkInList(som);
			if (index == -1) {
				index = meshArr.size();
				meshArr.push_back(som);
				std::vector<MeshDataInstance*> pol;
				instanceArr.push_back(pol);
			}
			instanceArr[index].push_back(som->meshInsData);
		}
		void AddMeshCall(std::vector<MeshInstance*>* som) {
			for (int i = 0; i < som->size(); i++) {
				AddMeshCall((*som)[i]);
			}
		}
		void updateUniform(int index, std::shared_ptr <Camera> cam) {
			//int index = checkInList(meshArr);
			const std::vector<MeshDataInstance*>& somTemp = instanceArr[index];
			std::shared_ptr<Shader> modelShader = meshArr[index]->shady;
			int count = 0;
			for(int i=0;i< somTemp.size();i++){
				somTemp[i]->objMaterial->bind(modelShader, i,count);
				std::string temp = "positionMatrix[" + std::to_string(i) + "]";
				modelShader->setUniformMatrix4fv(temp.c_str(),GL_FALSE,*somTemp[i]->positionMat);
				temp = "rotationMatrix[" + std::to_string(i) + "]";
				modelShader->setUniformMatrix4fv(temp.c_str(), GL_FALSE, *somTemp[i]->rotationMat);
				temp = "scaleMatrix[" + std::to_string(i) + "]";
				modelShader->setUniformMatrix4fv(temp.c_str(), GL_FALSE, *somTemp[i]->scaleMat);
			}

			int framebufferwidth = 800;
			int framebufferheight = 800;

			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 53.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			modelShader->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);

			cam->updateViewMatrix();
			cam->sendToShader(modelShader);

		}
		std::shared_ptr<Shader> getShaderFromMesh(int index) {
			int vertDist = meshArr[index]->objMesh->getVerticesDistribution();
			int vertShaderInput = 0;
			int fragShaderInput = 0;
			int fragShaderOutput = ShaderInit::ALBEDO_COLOR;
			if (vertDist & Mesh::N3F) {
				vertShaderInput |= ShaderInit::NORM_VERTIN;
				fragShaderInput |= ShaderInit::NORM_VERT;
			}
			if (vertDist & Mesh::T2F) {
				vertShaderInput |= ShaderInit::TEX_COORDIN;
				fragShaderInput |= ShaderInit::TEX_COORD;
			}

			std::shared_ptr<Material> meshMat = instanceArr[index][0]->objMaterial;

			if (meshMat->diffuseTex) {
				fragShaderInput |= ShaderInit::ALBEDO_TEX;
			}
			if (meshMat->specularTex) {
				fragShaderInput |= ShaderInit::SPECULAR_TEX;
			}
			ShaderInit somExample;
			std::string vertShader = somExample.getVertShader(vertShaderInput);
			std::string fragShader = somExample.getFragShader(fragShaderInput, fragShaderOutput);

			std::shared_ptr <gameEngine::Shader> modelShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader(vertShader, fragShader, ""));

			return modelShader;
		}
		void createShader() {
			ShaderInit som;
			for (int i = 0; i < meshArr.size(); i++) {
				if (!meshArr[i]->shady) {
					meshArr[i]->setShader(getShaderFromMesh(i));
				}
			}
		}
		void Draw(std::shared_ptr <Camera> cam) {
			
			for (int i = 0; i < meshArr.size();i++) {
				meshArr[i]->shady->Use();
				const MeshInstance& som = *meshArr[i];
				//update uniforms
				updateUniform(i, cam);
				//use uniform buffers
				som.objMesh->preDraw();
				som.objMesh->Draw(instanceArr[i].size());
				som.objMesh->postDraw();
				meshArr[i]->shady->unUse();
			}
			
		}
	};
	
}
