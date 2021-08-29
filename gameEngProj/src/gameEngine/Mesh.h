#pragma once
#include"libs.h"
#include"GameObject.h"
#include"CustomShader.h"
namespace gameEngine {
	class FUN_API Mesh :public sharedObj{
	private: 
		std::vector<float>vertices;
		std::vector<unsigned int>indices;
		/*std::vector<std::shared_ptr <Texture>>diffuseTex;
		std::vector< std::shared_ptr <Texture>>specularTex;*/
		unsigned int vbo;
		unsigned int ibo;
		unsigned int vao;

		int verticesDistribution;

		int getData(int som) {
			int count = 0;
			if (som & P3F) {
				count+=3;
			}
			else if (som & P2F) {
				count += 2;
			}
			if (som & N3F) {
				count += 3;
			}
			if (som & T2F) {
				count += 2;
			}
			return count;
		}
		void initBuffers(int distStyle) {
			verticesDistribution = distStyle;

			int dataCount = getData(distStyle);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

			if (indices.size() != 0) {
				glGenBuffers(1, &ibo);
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
			}
			else {
				ibo = -1;
			}
			

			int count = 0;
			int dataPrev = 0;
			//glBindBuffer(GL_ARRAY_BUFFER, vbo);
			if (distStyle & P3F) {
				glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, dataCount *sizeof(float), (void*)(dataPrev*sizeof(float)));
				glEnableVertexAttribArray(count);
				count++;
				dataPrev += 3;
			}
			else if (distStyle & P2F) {
				glVertexAttribPointer(count, 2, GL_FLOAT, GL_FALSE, dataCount *sizeof(float), (void*)(dataPrev*sizeof(float)));
				glEnableVertexAttribArray(count);
				count++;
				dataPrev += 2;
			}
			
			if (distStyle & N3F) {
				glVertexAttribPointer(count, 3, GL_FLOAT, GL_FALSE, dataCount * sizeof(float), (void*)(dataPrev*sizeof(float)));
				glEnableVertexAttribArray(count);
				count++;
				dataPrev += 3;
			}
			if (distStyle & T2F) {
				glVertexAttribPointer(count, 2, GL_FLOAT, GL_FALSE, dataCount * sizeof(float), (void*)(sizeof(float)*dataPrev));
				glEnableVertexAttribArray(count);
				count++;
				dataPrev += 2;
			}
			

		}

	public:
		enum dataDistribution {
			P3F=1,
			N3F=2,
			T2F=4,
			P2F=8
		};
		Mesh(std::vector<float>& vert, std::vector<unsigned int>& index_arr, int distr = P3F|N3F|T2F) {
			this->vertices = vert;
			this->indices = index_arr;
			//this->diffuseTex = diffuse_tex_mat;
			//this->diffuseTex.insert(this->diffuseTex.end(), diffuse_tex_mat.begin(), diffuse_tex_mat.end());
			//this->specularTex = specular_tex_mat;
			/*for (int i = 0; i < vert.size(); i++) {
				vertices.push_back(vert[i]);
			}
			for (int i = 0; i < index_arr.size(); i++) {
				indices.push_back(index_arr[i]);
			}
			*/

			initBuffers(distr);
		}
		void bindData() {
			glBindVertexArray(vao);
		}

		void preDraw() {

			bindData();

			//glActiveTexture(GL_TEXTURE0 + diffuseTex[0].getTextureUnit());
			//shader->setUniform1i("diffTex", diffuseTex[0].getTextureUnit());
			//glBindTexture(GL_TEXTURE_2D, diffuseTex[0].getID());
			//diffuseTex[0].bind();
			//shader->setUniform1i("diffTex", diffuseTex[0].getTextureUnit());
			//glBindVertexArray(vao);
			//shader->setUniform1i(("material" + std::to_string(0) + ".specularTex").c_str(), diffuseTex[i]->getTextureUnit());
			//diffuseTex[0].bind();
			//glDrawElementsInstanced(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0, 10000);
			
		}
		int getVerticesDistribution() {
			return verticesDistribution;
		}
		void Draw(int count) {
			if (ibo == -1 && count != 1) {
				glDrawArraysInstanced(GL_TRIANGLES, 0, vertices.size() / 3, count);
			}
			else if (ibo == -1) {
				glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
			}
			else if (count!=1) {
				glDrawElementsInstanced(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0, count);
			}
			else {
				glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
			}
		}

		void postDraw() {
			glBindVertexArray(0);
		}
		inline unsigned int getVAO() { return vao; }

		~Mesh() {
			glDeleteVertexArrays(1, &vao);
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
		}

	};


}
