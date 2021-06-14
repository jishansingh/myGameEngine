#pragma once
#include"libs.h"
#include"Texture.h"
#include"Shader.h"
#include"Material.h"
namespace gameEngine {
	class FUN_API Mesh :public sharedObj{
	private: 
		std::vector<Vertex>vertices;
		std::vector<unsigned int>indices;
		/*std::vector<std::shared_ptr <Texture>>diffuseTex;
		std::vector< std::shared_ptr <Texture>>specularTex;*/
		unsigned int vbo;
		unsigned int ibo;
		unsigned int vao;

		void initBuffers() {

			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);


			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texcoord));
			glEnableVertexAttribArray(2);

		}

	public:
		Mesh(std::vector<Vertex>& vert, std::vector<unsigned int>& index_arr) {
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

			initBuffers();
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
		void Draw(int count) {
			if (count!=1) {
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
