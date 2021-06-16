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
