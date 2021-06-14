#pragma once
#include"libs.h"
#include"renderObj.h"

namespace gameEngine {
	

	class Renderer {
		std::unordered_map< MeshInstance, std::vector<MeshDataInstance>> mesh_count;
	public:
		void AddMeshCall(MeshInstance som) {
			mesh_count[som].push_back(som.meshInsData);
		}
		void AddMeshCall(std::vector<MeshInstance> som) {
			for (int i = 0; i < som.size(); i++) {
				mesh_count[som[i]].push_back(som[i].meshInsData);
			}
		}
		void updateUniform(const MeshInstance& som) {
			const std::vector<MeshDataInstance>& somTemp = mesh_count[som];
			std::shared_ptr<Shader> modelShader = som.shady;
			int count = 0;
			for(int i=0;i< somTemp.size();i++){
				somTemp[i].objMaterial->bind(modelShader, i,count);
				std::string temp = "positionMatrix[" + std::to_string(i) + "]";
				modelShader->setUniformMatrix4fv(temp.c_str(),GL_FALSE,*somTemp[i].positionMat);
				temp = "rotationMatrix[" + std::to_string(i) + "]";
				modelShader->setUniformMatrix4fv(temp.c_str(), GL_FALSE, *somTemp[i].rotationMat);
				temp = "scaleMatrix[" + std::to_string(i) + "]";
				modelShader->setUniformMatrix4fv(temp.c_str(), GL_FALSE, *somTemp[i].scaleMat);
				count += 1;
			}
		}
		void Draw() {
			for (auto it = mesh_count.begin(); it != mesh_count.end(); it++) {
				const MeshInstance som = it->first;
				som.shady->Use();
				//update uniforms
				updateUniform(som);
				//use uniform buffers
				som.objMesh->preDraw();
				som.objMesh->Draw(it->second.size());
				som.objMesh->postDraw();
			}
		}
	};
}
