#pragma once
#include"Core.h"
#include"libs.h"
#include"Shader.h"




namespace gameEngine {

	class shaderUniform {
	public:
		std::string name;
		enum dataType {
			MATRIX=1,
			VECTOR=2,
			FLOAT=4,
			INT=8,
			TEXTURE=16
		};
		int state;
		int dimVal;
		void* value;
		shaderUniform(int stateVal, std::string _name, void* somVal, int dimension) {
			value = somVal;
			name = _name;
			dimVal = dimension;
			state = stateVal;
		}
		void setVal(void* somVal) {
			value = somVal;
		}
		void bind(Shader* som){
			if (value == NULL) {
				return;
			}
			if (state & MATRIX) {
				switch (dimVal)
				{
				case 2:
					if (state & FLOAT) {
						glUniformMatrix2fv(glGetUniformLocation(som->getID(), name.c_str()), 1, GL_FALSE, (GLfloat*)(value));
					}
					break;
				case 3:
					if (state & FLOAT) {
						glUniformMatrix3fv(glGetUniformLocation(som->getID(), name.c_str()), 1, GL_FALSE, (GLfloat*)(value));
					}
					break;
				case 4:
					if (state & FLOAT) {
						glUniformMatrix4fv(glGetUniformLocation(som->getID(), name.c_str()), 1, GL_FALSE, (GLfloat*)(value));
					}
					break;
				default:
					break;
				}
			}
			else if (state & VECTOR) {
				switch (dimVal)
				{
				case 1:
					if (state & FLOAT) {
						glUniform1fv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLfloat*)(value));
					}
					else if (state & INT) {
						glUniform1iv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLint*)(value));
					}
					break;
				case 2:
					if (state & FLOAT) {
						glUniform2fv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLfloat*)(value));
					}
					else if (state & INT) {
						glUniform2iv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLint*)(value));
					}
					break;
				case 3:
					if (state & FLOAT) {
						glUniform3fv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLfloat*)(value));
					}
					else if (state & INT) {
						glUniform3iv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLint*)(value));
					}
					break;
				case 4:
					if (state & FLOAT) {
						glUniform4fv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLfloat*)(value));
					}
					else if (state & INT) {
						glUniform4iv(glGetUniformLocation(som->getID(), name.c_str()), 1, (GLint*)(value));
					}
					break;
				default:
					break;
				}
			}
		}
		
	};

	class ShaderInit {
	public:
		int state;
		enum VERT_SHADER_INPUT {
			NORM_VERTIN = 2,
			TEX_COORDIN = 4,
			INSTANCED = 8
		};
		enum FRAG_SHADER_INPUT {
			NORM_COLOR_INST = 1,
			NORM_COLOR = 2,
			NORM_CONST = 4,
			NORM_CONST_INST = 8,
			NORM_VERT = 16,
			TEX_COORD = 32,
			ROUGH_CONST = 64,
			ROUGH_MAP = 128,
			ROUGH_CONST_INST = 128*2,
			ROUGH_MAP_INST   = 128*4,
			ALBEDO_CONST     = 128*8,
			ALBEDO_TEX       = 128*16,
			ALBEDO_CONST_INST = 128 * 32,
			ALBEDO_TEX_INST = 128 * 64,
			SPECULAR_TEX = 128*128,
			SPECULAR_TEX_INST = 128 * 128
		};

		enum FRAG_SHADER_OUTPUT {
			POSITION = 1,
			ALBEDO_COLOR = 2,
			SPECULAR_OUT = 4,
			NORMAL_TEX=8,
			ROUGHNESS_TEX = 16,
			
		};
		enum UNIFORM_TYPE {
			INT = 1,
			FLOAT = 2,
			DOUBLE = 4,
			INT_ARR = 8,
			FLOAT_ARR = 16,
			DOUBLE_ARR = 32,
			MAT_4X4 = 64,
			MAT_4X4_ARR = 128,
			FTEXTURE = 128*2,
			ITEXTURE = 128*4,
			DTEXTURE = 128*8,
			FTEXTURE_ARR = 128*16,
			ITEXTURE_ARR = 128*32,
			DTEXTURE_ARR = 128*64,
		};
		ShaderInit() {
			state = 0;
		}
		void addVertUniform(int type, void* data,int size=1) {
			if (type & INT) {

			}
		}
		std::string getVertShader(int vertState,int size=1) {
			state = vertState;
			std::string vertShaderString = "#version 440\n";
			int count = 0;
			vertShaderString+= "layout(location = "+std::to_string(count)+") in vec3 vs_position;\n";
			count++;
			if (vertState & NORM_VERTIN) {
				vertShaderString += "layout(location = " + std::to_string(count) + ") in vec3 vs_normal;\n";
				count++;
			}
			if (vertState & TEX_COORDIN) {
				vertShaderString += "layout (location = " + std::to_string(count) + ") in vec2 vs_texcoord;\n";
				count++;
			}
			if (vertState & INSTANCED) {
				vertShaderString += "uniform mat4 positionMatrix[" + std::to_string(size) + "];\n";
				vertShaderString += "uniform mat4 rotationMatrix[" + std::to_string(size) + "];\n";
				vertShaderString += "uniform mat4 scaleMatrix[" + std::to_string(size) + "];\n";
			}
			else {
				vertShaderString += "uniform mat4 positionMatrix[1];\n";
				vertShaderString += "uniform mat4 rotationMatrix[1];\n";
				vertShaderString += "uniform mat4 scaleMatrix[1];\n";
			}
			vertShaderString += "uniform mat4 viewMatrix;\n";
			vertShaderString += "uniform mat4 projectionMatrix;\n";

			if (vertState & INSTANCED) {
				vertShaderString += "uniform mat4 offsets[" + std::to_string(size) + "];\n";
			}


			vertShaderString += "out vec3 fs_position;\n";
			if (vertState & NORM_VERTIN) {
				vertShaderString += "out vec3 fs_normal;\n";
			}
			if (vertState & TEX_COORDIN) {
				vertShaderString += "out vec2 fs_texcoord;\n";
			}

			vertShaderString += "void main(){\n";
			if (vertState & INSTANCED) {
				vertShaderString += "vec4 somPos = positionMatrix[gl_InstanceID]*rotationMatrix[gl_InstanceID]*scaleMatrix[gl_InstanceID]*vec4(vs_position,1.f);\n";
			}
			else {
				vertShaderString += "vec4 somPos = positionMatrix[0]*rotationMatrix[0]*scaleMatrix[0]*vec4(vs_position,1.f);\n";
			}
			
			if (vertState & NORM_VERTIN) {
				vertShaderString += "fs_normal = vec3(rotationMatrix[0]*vec4(vs_normal,1.f));\n";
			}
			if (vertState & TEX_COORDIN) {
				vertShaderString += "fs_texcoord = vs_texcoord;\n";
			}
			vertShaderString += "gl_Position = projectionMatrix*viewMatrix*somPos;\n";
			vertShaderString += "fs_position = somPos.xyz;\n";

			vertShaderString += "}";
			return vertShaderString;
		}

		std::vector<shaderUniform*> getUniforms(int vertState, int fragInp, int size = 1) {
			std::vector<shaderUniform*> somTemp;
			if (vertState & INSTANCED) {
				for (int i = 0; i < size; i++) {
					somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "positionMatrix[" + std::to_string(i) + "]", NULL, 4));
					somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "rotationMatrix[" + std::to_string(size) + "]", NULL, 4));
					somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "scaleMatrix[" + std::to_string(size) + "]", NULL, 4));
				}
			}
			else {
				for (int i = 0; i < size; i++) {
					somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "positionMatrix[" + std::to_string(i) + "]", NULL, 4));
					somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "rotationMatrix[" + std::to_string(i) + "]", NULL, 4));
					somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "scaleMatrix[" + std::to_string(i) + "]", NULL, 4));
				}
			}
			somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "viewMatrix", NULL, 4));
			somTemp.push_back(new shaderUniform(shaderUniform::MATRIX| shaderUniform::FLOAT, "projectionMatrix", NULL, 4));

			for (int i = 0; i < size; i++) {
				somTemp.push_back(new shaderUniform(shaderUniform::VECTOR | shaderUniform::INT, "materialData[" + std::to_string(i) + "].albedoTex", NULL, 1));
				somTemp.push_back(new shaderUniform(shaderUniform::VECTOR | shaderUniform::INT, "materialData[" + std::to_string(i) + "].specularTex", NULL, 1));
				somTemp.push_back(new shaderUniform(shaderUniform::VECTOR | shaderUniform::INT, "materialData[" + std::to_string(i) + "].normalTex", NULL, 1));
			}

			return somTemp;
		}

		std::string getFragShader(int fragInp, int fragOut, int size=1) {
			std::string fragShaderString="#version 440\n";
			int count = 0;
			if (fragOut & POSITION) {
				fragShaderString += "layout(location = " + std::to_string(count) + ") out vec4 fso_color;\n";
				count++;
			}
			if (fragOut & ALBEDO_COLOR) {
				fragShaderString += "layout(location = " + std::to_string(count) + ") out vec4 fso_albedo;\n";
				count++;
			}
			if (fragOut & SPECULAR_OUT) {
				fragShaderString += "layout(location = " + std::to_string(count) + ") out vec3 fso_specular;\n";
				count++;
			}
			if (fragOut & NORMAL_TEX) {
				fragShaderString += "layout(location = " + std::to_string(count) + ") out vec3 fso_normal;\n";
				count++;
			}
			if (fragOut & ROUGHNESS_TEX) {
				fragShaderString += "layout(location = " + std::to_string(count) + ") out vec3 fso_rough;\n";
				count++;
			}
			fragShaderString += "in vec3 fs_position;\n";
			if (fragInp & NORM_VERT) {
				fragShaderString += "in vec3 fs_normal;\n";
			}
			if (fragInp & TEX_COORD) {
				fragShaderString += "in vec2 fs_texcoord;\n";
			}

			fragShaderString += "\
				#define DEF_NORMAL vec3(0.f,0.f,1.f)\n\
				#define DEF_ROUGH 1.f\n\
				#define DEF_SPECULAR vec3(0.f)\n\
				#define DEF_COLOR vec4(1.f,0.f,0.f,1.f)\n";
			//normal
			/*if (fragInp & NORM_COLOR_INST) {
				fragShaderString += "uniform sampler2D normal_tex["+std::to_string(size)+"];\n";
			}
			else if (fragInp & NORM_COLOR) {
				fragShaderString += "uniform sampler2D normal_tex;\n";
			}
			else if (fragInp & NORM_CONST) {
				fragShaderString += "uniform vec3 normal_tex;\n";
			}*/

			fragShaderString += "struct Material{\n";
			fragShaderString += "   sampler2D albedoTex;\n";
			fragShaderString += "   sampler2D specularTex;\n";
			fragShaderString += "   sampler2D normalTex;\n";
			fragShaderString += "   };\n";

			/*
			//albedo
			if (fragInp & ALBEDO_CONST) {
				fragShaderString += "uniform vec4 albedo;\n";
			}
			else if (fragInp & ALBEDO_TEX) {
				fragShaderString += "uniform sampler2D albedo;\n";
			}
			else if (fragInp & ALBEDO_CONST_INST) {
				fragShaderString += "uniform vec4 albedo[" + std::to_string(size) + "];\n";
			}
			else if (fragInp & ALBEDO_TEX_INST) {
				fragShaderString += "uniform sampler2D albedo[" + std::to_string(size) + "];\n";
			}
			else {
				fragShaderString += "const vec4 albedo = DEF_COLOR;";
			}

			//specularTex
			if (fragInp & SPECULAR_TEX) {
				fragShaderString += "uniform vec4 specCol;\n";
			}
			else if (fragInp & SPECULAR_TEX_INST) {
				fragShaderString += "uniform sampler2D specCol;\n";
			}
			else {
				fragShaderString += "const vec3 specCol = DEF_SPECULAR;\n";
			}

			//roughness
			if (fragInp & ROUGH_CONST) {
				fragShaderString += "uniform float roughness;\n";
			}
			else if (fragInp & ROUGH_MAP) {
				fragShaderString += "uniform sampler2D roughness;\n";
			}
			else if (fragInp & ROUGH_CONST_INST) {
				fragShaderString += "uniform float roughness["+std::to_string(size)+"];\n";
			}
			else if (fragInp & ROUGH_MAP_INST) {
				fragShaderString += "uniform sampler2D roughness[" + std::to_string(size) + "];\n";
			}
			else {
				fragShaderString += "const float roughness = DEF_ROUGH;\n";
			}
			fragShaderString += "};\n";*/


			
			fragShaderString += "uniform Material materialData["+std::to_string(size)+"];\n";

			//main function starts

			fragShaderString += "void main(){\n";
			if (fragOut & NORM_VERT) {
				fragShaderString += "fso_normal = fs_normal;\n";
			}
			else if (fragOut & NORM_COLOR_INST) {
				fragShaderString += "fso_normal = texture(materialData[gl_InstanceID].normalTex,fs_texcoord).rgb;\n";
			}
			else if(fragOut& NORMAL_TEX){
				fragShaderString += "fso_normal = texture(materialData[0].normalTex,fs_texcoord).rgb;\n";
			}
			//roughness
			if (fragOut & ROUGHNESS_TEX) {
				if (fragInp & ROUGH_CONST) {
					fragShaderString += "fso_rough = vec3(materialData[0].roughness);\n";
				}
				else if (fragInp & ROUGH_MAP) {
					//not enabled for now
					fragShaderString += "fso_rough = texture(materialData[0].roughness,fs_texcoord).rgb;\n";
				}
				else if (fragInp & ROUGH_CONST_INST) {
					fragShaderString += "fso_rough =  vec3(materialData[gl_InstanceID].roughness[gl_InstanceID]);\n";
				}
				else if (fragInp & ROUGH_MAP_INST) {
					//not enabled for now
					fragShaderString += "fso_rough = texture(materialData[gl_InstanceID].roughness,fs_texcoord).rgb;\n";
				}
			}

			if (fragOut & ALBEDO_COLOR) {
				if (fragInp & ALBEDO_CONST) {
					//not enabled for now
					fragShaderString += "fso_albedo = albedo;\n";
				}
				else if (fragInp & ALBEDO_TEX) {
					fragShaderString += "fso_albedo = texture(materialData[0].albedoTex,fs_texcoord);\n";
				}
				else if (fragInp & ALBEDO_CONST_INST) {
					//not enabled for now
					fragShaderString += "fso_albedo = albedo[gl_InstanceID];\n";
				}
				else if (fragInp & ALBEDO_TEX_INST) {
					fragShaderString += "fso_albedo = texture(materialData[gl_InstanceID].albedoTex,fs_texcoord);\n";
				}
			}

			//specularTex
			if (fragOut & SPECULAR_OUT) {
				if (fragInp & SPECULAR_TEX) {
					fragShaderString += "fso_specular = texture(materialData[0].specularTex,fs_texcoord).rgb;\n";
				}
				else if (fragInp & SPECULAR_TEX_INST) {
					fragShaderString += "fso_specular = texture(materialData[gl_InstanceID].specularTex,fs_texcoord).rgb;\n";
				}
				else {
					fragShaderString += "fso_specular = specCol;\n";
				}
			}


			/*
			//normal
			if (fragInp & NORM_COLOR_INST) {
				fragShaderString += "fso_normal = texture(normal_tex[gl_InstanceID],fs_texcoord).rgb;\n";
			}
			else if (fragInp & NORM_COLOR) {
				fragShaderString += "fso_normal = texture(normal_tex,fs_texcoord).rgb;\n";
			}
			else if (fragInp & NORM_CONST) {
				fragShaderString += "fso_normal = normal_tex;\n";
			}
			else if (fragInp & NORM_VERT) {
				fragShaderString += "fso_normal = fs_normal;\n";
			}
			else if (fragOut & NORMAL_TEX) {
				fragShaderString += "fso_normal = DEF_NORMAL;\n";
			}
			//roughness
			if (fragOut & ROUGHNESS_TEX) {
				if (fragInp & ROUGH_CONST) {
					fragShaderString += "fso_rough = vec3(roughness);\n";
				}
				else if (fragInp & ROUGH_MAP) {
					fragShaderString += "fso_rough = texture(roughness,fs_texcoord).rgb;\n";
				}
				else if (fragInp & ROUGH_CONST_INST) {
					fragShaderString += "fso_rough =  vec3(roughness[gl_InstanceID]);\n";
				}
				else if (fragInp & ROUGH_MAP_INST) {
					fragShaderString += "fso_rough = texture(roughness[gl_InstanceID],fs_texcoord).rgb;\n";
				}
			}
			
			//albedo
			if (fragOut & ALBEDO_COLOR) {
				if (fragInp & ALBEDO_CONST) {
					fragShaderString += "fso_albedo = albedo;\n";
				}
				else if (fragInp & ALBEDO_TEX) {
					fragShaderString += "fso_albedo = texture(albedo,fs_texcoord);\n";
				}
				else if (fragInp & ALBEDO_CONST_INST) {
					fragShaderString += "fso_albedo = albedo[gl_InstanceID];\n";
				}
				else if (fragInp & ALBEDO_TEX_INST) {
					fragShaderString += "fso_albedo = texture(albedo[gl_InstanceID],fs_texcoord);\n";
				}
			}

			//specularTex
			if (fragOut & SPECULAR_OUT) {
				if (fragInp & SPECULAR_TEX) {
					fragShaderString += "fso_specular = texture(specCol,fs_texcoord).rgb;\n";
				}
				else if (fragInp & SPECULAR_TEX_INST) {
					fragShaderString += "fso_specular = texture(specCol[gl_InstanceID],fs_texcoord).rgb;\n";
				}
				else {
					fragShaderString += "fso_specular = specCol;\n";
				}
			}*/
			fragShaderString += "}";

			return fragShaderString;

		}
	};
	
}


