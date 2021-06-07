#pragma once
#include"Shader.h"
#include"Texture.h"
#include"Model.h"

namespace gameEngine {
	class FUN_API ObjectRender :public GameObj {
	public:
		virtual void updateModelMatrix() {}
		virtual void updateProjMatrix(GLFWwindow* window) {}
		virtual void Draw(const bool instanced=false, const int count = 1) {}
		virtual std::shared_ptr <Shader> getShader() { return NULL; }
		virtual ~ObjectRender(){}
		inline glm::vec3 getPosition() {
			return glm::vec3(0.f);
		}
		inline glm::vec3 getRotation() {
			return glm::vec3(0.f);
		}
	};


	class FUN_API Quad :public ObjectRender {
		std::shared_ptr <Shader> shady;
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;
		glm::vec3 position;
		glm::vec3 rotation;
		float size = 1.f;
		std::vector<std::shared_ptr<Texture>> textures;
	public:
		Quad(glm::vec3 pos,glm::vec3 rot,float width, float height, std::shared_ptr<Shader> QShad ,const float offset=0.01f) {
			shady = QShad;
			position = pos;
			rotation = rot;
			float farWid = 1.f;
			float vertices_box[16]{
				-1 * (width - offset),  (height - offset),0.f,farWid,
				-1 * (width - offset), -1 * (height - offset),0.f,0.f,
				 (width - offset), -1 * (height - offset),farWid,0.f,
				 (width - offset),  (height - offset),farWid,farWid
			};
			unsigned int noOfVertices = sizeof(vertices_box) / (4 * sizeof(float));
			GLuint indVert[] = {
				2,1,0,
				3,2,0
			};
			glBindVertexArray(0);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, noOfVertices * 4 * sizeof(float), &vertices_box[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indVert, GL_STATIC_DRAW);
		}
		Quad(glm::vec3 pos, glm::vec3 rot, float width, float height, const float offset = 0.01f) {
			position = pos;
			rotation = rot;
			float farWid = 2 * (width - offset);
			/*float vertices_box[16]{
				0.f,2 * (height - offset),0.f,1.f,
				0.f,0.f,0.f,0.f,
				2 * (width - offset),0.f,1.f,0.f,
				2 * (width - offset),2 * (height - offset),1.f,1.f
			};*/
			float vertices_box[16]{
				-1*(width - offset),  (height - offset),0.f,1.f,
				-1*(width - offset), -1*(height - offset),0.f,0.f,
				 (width - offset), -1*(height - offset),1.f,0.f,
				 (width - offset),  (height - offset),1.f,1.f
			};
			unsigned int noOfVertices = sizeof(vertices_box) / (4 * sizeof(float));
			GLuint indVert[] = {
				2,1,0,
				3,2,0
			};
			glBindVertexArray(0);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, noOfVertices * 4 * sizeof(float), &vertices_box[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glGenBuffers(1, &ibo);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(GLuint), indVert, GL_STATIC_DRAW);
		}
		~Quad() {
			glDeleteBuffers(1, &vbo);
			glDeleteBuffers(1, &ibo);
			glDeleteVertexArrays(1, &vao);
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		void addTexture(std::shared_ptr <Texture> tex) {
			textures.push_back(tex);
		}
		void setShader(std::shared_ptr <Shader> somShader) {
			shady = somShader;
		}
		void replaceTex(int i, std::shared_ptr <Texture> tex) {
			if (i > textures.size()) {
				return;
			}
			else if (i == textures.size()) {
				textures.push_back(tex);
				return;
			}
			//how to lose shared_ptr
			//delete textures[i];
			textures[i] = tex;
		}
		void updateModelMatrix() {
			glm::mat4 modelMatrix(1.f);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(size));
			shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		}
		void updateProjMatrix(GLFWwindow* window) {
			int framebufferwidth;
			int framebufferheight;
			glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 53.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}
		void setSize(float inp) {
			size = inp;
		}
		void Draw(const bool instanced = false, const int count = 1) {
			shady->Use();

			for (int i = 0; i < textures.size();i++) {
				textures[i]->bind();
				std::string temp = "texture" + std::to_string(i);
				shady->setUniform1i(temp.c_str(), textures[i]->getTextureUnit());
			}
			glBindVertexArray(vao);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
		void onkeyPress(int key){}
		std::shared_ptr<Shader> getShader() {
			return shady;
		}
		
	};

	class FUN_API modelLoader :public ObjectRender {
		std::shared_ptr <Model> model;
		std::shared_ptr <Shader> shady;
		glm::vec3 position;
		glm::vec3 rotation;
	public:
		modelLoader(const char* path, glm::vec3 pos, glm::vec3 rot, std::shared_ptr <Shader> shaderM) :
			position(pos), rotation(rot) {
			shady = shaderM;
			model = std::make_shared<Model>(*new Model(path));
		}
		~modelLoader() {
		}
		std::shared_ptr <Shader> getShader() {
			return shady;
		}
		void setShader(std::shared_ptr <Shader> somShader) {
			shady = somShader;
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		void updateModelMatrix() {
			glm::mat4 modelMatrix(1.f);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
			shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		}
		void updateProjMatrix(GLFWwindow* window) {
			int framebufferwidth;
			int framebufferheight;
			glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 45.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}
		void Draw(const bool instanced = false, const int count = 1) {
			model->Draw(shady, instanced, count);
		}
	};

	class FUN_API instancedRenderer :public ObjectRender {
		std::shared_ptr<ObjectRender> instancedObj;
		std::vector<glm::vec3*> positions;
		std::vector<glm::vec3*> color;
	public:
		instancedRenderer(std::shared_ptr<ObjectRender> orgObj) {
			instancedObj = orgObj;
		}
		void updateModelMatrix() {
			sendToShader();
		}
		void updateProjMatrix(GLFWwindow* window) {
			instancedObj->updateProjMatrix(window);
		}
		void Draw(const bool instanced = false, const int count = 1) {
			sendToShader();
			instancedObj->Draw(true,positions.size());
		}
		std::shared_ptr <Shader> getShader() { return instancedObj->getShader(); }

		inline glm::vec3 getPosition() {
			return instancedObj->getPosition();
		}
		inline glm::vec3 getRotation() {
			return instancedObj->getRotation();
		}
		void addInstance(glm::vec3 pos, glm::vec3 col) {
			positions.push_back(new glm::vec3(pos));
			color.push_back(new glm::vec3(col));
		}
		void updateDataIndex(int index) {
			glm::mat4 modelMatrix(1.f);
			modelMatrix = glm::translate(modelMatrix, *positions[index]);
			modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
			std::string temp = "offsets[" + std::to_string(index) + "]";
			this->getShader()->setUniformMatrix4fv(temp.c_str(), GL_FALSE, modelMatrix);
			temp = "colors[" + std::to_string(index) + "]";
			this->getShader()->setUniform3f(temp.c_str(), GL_FALSE, *color[index]);
		}
		void setPosition(std::vector<glm::vec3*> pos, std::vector<glm::vec3*> col) {
			positions = pos;
			color = col;
		}

		void sendToShader() {
			for (int i = 0; i < positions.size(); i++) {
				glm::mat4 modelMatrix(1.f);
				modelMatrix = glm::translate(modelMatrix, *positions[i]);
				modelMatrix = glm::scale(modelMatrix, glm::vec3(1.f));
				std::string temp = "offsets[" + std::to_string(i) + "]";
				this->getShader()->setUniformMatrix4fv(temp.c_str(), GL_FALSE, modelMatrix);
				temp = "colors[" + std::to_string(i) + "]";
				this->getShader()->setUniform3f(temp.c_str(), GL_FALSE, *color[i]);
			}
		}
	};
	class FUN_API Cube :public ObjectRender {
		std::shared_ptr <Shader> shady;
		unsigned int vao;
		unsigned int vbo;
		unsigned int ibo;
		float size;
		glm::vec3 position;
		glm::vec3 rotation;
		std::vector<std::shared_ptr<Texture>> textures;
	public:
		Cube(glm::vec3 pos, glm::vec3 rot, float length, float width, float height, std::shared_ptr<Shader> QShad, const float offset = 0.01f) {
			size = 1.f;
			shady = QShad;
			position = pos;
			rotation = rot;
			length /= 2;
			width /= 2;
			height /= 2;
			float farWid = 1.f;
			float vertices[] = {
				// back face
				-length, -height, -width,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				 length,  height, -width,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				 length, -height, -width,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				 length,  height, -width,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				-length, -height, -width,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				-length,  height, -width,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face	   
				-length, -height,  width,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				 length, -height,  width,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				 length,  height,  width,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				 length,  height,  width,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-length,  height,  width,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-length, -height,  width,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face	   
				-length,  height,  width, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-length,  height, -width, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-length, -height, -width, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-length, -height, -width, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-length, -height,  width, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-length,  height,  width, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face	   
				 length,  height,  width,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 length, -height, -width,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 length,  height, -width,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				 length, -height, -width,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 length,  height,  width,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 length, -height,  width,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face	   
				-length, -height, -width,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				 length, -height, -width,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				 length, -height,  width,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				 length, -height,  width,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-length, -height,  width,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-length, -height, -width,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face		  
				-length,  height, -width,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				 length,  height , width,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				 length,  height, -width,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				 length,  height,  width,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-length,  height, -width,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-length,  height,  width,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
			};

			unsigned int noOfVertices = sizeof(vertices) / (8 * sizeof(float));

			glBindVertexArray(0);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, noOfVertices * 8 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		Cube(glm::vec3 pos, glm::vec3 rot, float length, float width, float height, const float offset = 0.01f) {
			size = 1.f;
			position = pos;
			rotation = rot;
			length /= 2;
			width /= 2;
			height /= 2;
			float farWid = 1.f;
			float vertices[] = {
				// back face
				-length, -height, -width,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				 length,  height, -width,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				 length, -height, -width,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
				 length,  height, -width,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
				-length, -height, -width,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
				-length,  height, -width,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
				// front face	   
				-length, -height,  width,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				 length, -height,  width,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
				 length,  height,  width,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				 length,  height,  width,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
				-length,  height,  width,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
				-length, -height,  width,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
				// left face	   
				-length,  height,  width, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				-length,  height, -width, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
				-length, -height, -width, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-length, -height, -width, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
				-length, -height,  width, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-length,  height,  width, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
				// right face	   
				 length,  height,  width,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 length, -height, -width,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 length,  height, -width,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
				 length, -height, -width,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
				 length,  height,  width,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
				 length, -height,  width,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
				// bottom face	   
				-length, -height, -width,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				 length, -height, -width,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
				 length, -height,  width,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				 length, -height,  width,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
				-length, -height,  width,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
				-length, -height, -width,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
				// top face		  
				-length,  height, -width,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				 length,  height , width,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				 length,  height, -width,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
				 length,  height,  width,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
				-length,  height, -width,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
				-length,  height,  width,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
			};

			unsigned int noOfVertices = sizeof(vertices) / (8 * sizeof(float));

			glBindVertexArray(0);
			glGenVertexArrays(1, &vao);
			glBindVertexArray(vao);

			glGenBuffers(1, &vbo);
			glBindBuffer(GL_ARRAY_BUFFER, vbo);
			glBufferData(GL_ARRAY_BUFFER, noOfVertices * 8 * sizeof(float), &vertices[0], GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);
			glEnableVertexAttribArray(0);

			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
			glEnableVertexAttribArray(2);
		}
		~Cube() {
			glDeleteBuffers(1, &vbo);
			//glDeleteBuffers(1, &ibo);
			glDeleteVertexArrays(1, &vao);
		}
		inline glm::vec3 getPosition() {
			return position;
		}
		inline glm::vec3 getRotation() {
			return rotation;
		}
		void addTexture(std::shared_ptr <Texture> tex) {
			textures.push_back(tex);
		}
		void setShader(std::shared_ptr <Shader> somShader) {
			shady = somShader;
		}
		void replaceTex(int i, std::shared_ptr <Texture> tex) {
			if (i > textures.size()) {
				return;
			}
			else if (i == textures.size()) {
				textures.push_back(tex);
				return;
			}
			//how to lose shared_ptr
			//delete textures[i];
			textures[i] = tex;
		}
		void setSize(float ko) {
			size = ko;
		}
		void updateModelMatrix() {
			glm::mat4 modelMatrix(1.f);
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.x), glm::vec3(1.f, 0.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.y), glm::vec3(0.f, 1.f, 0.f));
			modelMatrix = glm::rotate(modelMatrix, glm::radians(rotation.z), glm::vec3(0.f, 0.f, 1.f));
			modelMatrix = glm::scale(modelMatrix, glm::vec3(size));
			shady->setUniformMatrix4fv("modelMatrix", GL_FALSE, modelMatrix);
		}
		void updateProjMatrix(GLFWwindow* window) {
			int framebufferwidth;
			int framebufferheight;
			glfwGetFramebufferSize(window, &framebufferwidth, &framebufferheight);
			glm::mat4 projMatrix(1.f);
			float nearPlane = 0.1f;
			float farPlane = 100.f;
			float fov = 53.f;
			projMatrix = glm::perspective(glm::radians(fov), static_cast<float>(framebufferwidth) / framebufferheight, nearPlane, farPlane);
			shady->setUniformMatrix4fv("projectionMatrix", GL_FALSE, projMatrix);
		}

		void Draw(const bool instanced = false, const int count = 1) {
			shady->Use();

			for (int i = 0; i < textures.size(); i++) {
				textures[i]->bind();
				std::string temp = "texture" + std::to_string(i);
				shady->setUniform1i(temp.c_str(), textures[i]->getTextureUnit());
			}
			glBindVertexArray(vao);

			if (instanced) {
				glDrawArraysInstanced(GL_TRIANGLES, 0, 36, count);
			}
			else {
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}
		void onkeyPress(int key) {}
		std::shared_ptr<Shader> getShader() {
			return shady;
		}

	};

}
