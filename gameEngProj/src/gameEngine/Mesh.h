#pragma once
#include"libs.h"
#include"Texture.h"
#include"Shader.h"
class Mesh {
private:
	std::vector<Vertex>vertices;


	std::vector<Texture*>specularTex;
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
	std::vector<Texture*>diffuseTex;
	std::vector<unsigned int>indices;
	Mesh(std::vector<Vertex>& vert, std::vector<unsigned int>& index_arr, std::vector<Texture*> diffuse_tex_mat, std::vector<Texture*> specular_tex_mat) {

		this->vertices = vert;
		this->indices = index_arr;
		this->diffuseTex = diffuse_tex_mat;
		//this->diffuseTex.insert(this->diffuseTex.end(), diffuse_tex_mat.begin(), diffuse_tex_mat.end());
		this->specularTex = specular_tex_mat;
		/*for (int i = 0; i < vert.size(); i++) {
			vertices.push_back(vert[i]);
		}
		for (int i = 0; i < index_arr.size(); i++) {
			indices.push_back(index_arr[i]);
		}
		for (int i = 0; i < diffuse_tex_mat.size(); i++) {
			diffuseTex.push_back(&diffuse_tex_mat[i]);
		}
		for (int i = 0; i < specular_tex_mat.size(); i++) {
			specularTex.push_back(&specular_tex_mat[i]);
		}*/

		initBuffers();
	}
	void Draw(Shader* shader) {
		shader->Use();

		glBindVertexArray(vao);


		for (int i = 0; i < diffuseTex.size(); i++) {
			//diffuseTex[i]->bind();
			shader->Use();
			glActiveTexture(GL_TEXTURE0 + diffuseTex[i]->getTextureUnit());
			shader->setUniform1i(("material" + std::to_string(i) + ".diffuseTex").c_str(), diffuseTex[i]->getTextureUnit());
			//shader->setUniform1i("diffTex", diffuseTex[i]->getTextureUnit());
			glBindTexture(GL_TEXTURE_2D, diffuseTex[i]->getID());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		}

		for (int i = 0; i < specularTex.size(); i++) {
			//diffuseTex[i]->bind();
			shader->Use();
			glActiveTexture(GL_TEXTURE0 + diffuseTex[i]->getTextureUnit());
			shader->setUniform1i(("material" + std::to_string(i) + ".specularTex").c_str(), diffuseTex[i]->getTextureUnit());
			glBindTexture(GL_TEXTURE_2D, diffuseTex[i]->getID());
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			//std::cout << glGetError() << std::endl;
		}
		shader->Use();
		for (int i = 0; i < diffuseTex.size(); i++) {
			diffuseTex[i]->bind();
		}
		for (int i = 0; i < specularTex.size(); i++) {
			specularTex[i]->bind();
		}

		shader->Use();
		glBindVertexArray(vao);
		//glActiveTexture(GL_TEXTURE0 + diffuseTex[0].getTextureUnit());
		//shader->setUniform1i("diffTex", diffuseTex[0].getTextureUnit());
		//glBindTexture(GL_TEXTURE_2D, diffuseTex[0].getID());
		//diffuseTex[0].bind();
		//shader->setUniform1i("diffTex", diffuseTex[0].getTextureUnit());
		//glBindVertexArray(vao);
		//shader->setUniform1i(("material" + std::to_string(0) + ".specularTex").c_str(), diffuseTex[i]->getTextureUnit());
		//diffuseTex[0].bind();
		//glDrawElementsInstanced(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0, 10000);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

	}
	inline unsigned int getVAO() { return vao; }

};

