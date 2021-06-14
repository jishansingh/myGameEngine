#pragma once
#include"libs.h"
#include"Texture.h"
namespace gameEngine {

	class FUN_API defMaterial {
	public:
		std::shared_ptr <Texture>diffuseTex;
		std::shared_ptr <Texture>specularTex;
		defMaterial() {
			char som[] = { 255,0,0 };
			diffuseTex = std::make_shared<Texture>(*new Texture(GL_TEXTURE_2D, GL_SRGB, GL_RGBA, GL_UNSIGNED_BYTE, 1, 1, som));
			specularTex = std::make_shared<Texture>(*new Texture(GL_TEXTURE_2D, GL_SRGB, GL_RGBA, GL_UNSIGNED_BYTE, 1, 1, som));
		}
		static std::shared_ptr <defMaterial> defaultMat;
		static std::shared_ptr <defMaterial> initDefMat() {
			if (!defaultMat) {
				defaultMat = std::make_shared<defMaterial>(*new defMaterial());
			}
			return defaultMat;
		}
		static std::shared_ptr <Texture> getDefaultDiffuseTex() {
			return initDefMat()->diffuseTex;
		}
		static std::shared_ptr <Texture> getDefaultSpecularTex() {
			return initDefMat()->specularTex;
		}
	};

	class FUN_API Material {
	public:
		std::shared_ptr <Texture>diffuseTex;
		std::shared_ptr <Texture>specularTex;
		glm::vec3 diffuseColor;
		glm::vec3 specColor;
		float roughness = 0.5f;
		Material(Texture* dTex, Texture* sTex) {
			diffuseTex = std::make_shared<Texture>(*dTex);
			specularTex = std::make_shared<Texture>(*sTex);
		}
		Material(std::shared_ptr <Texture>sTex) {
			diffuseTex = defMaterial::getDefaultDiffuseTex();
			specularTex = sTex;
		}
		Material(std::shared_ptr <Texture>dTex) {
			diffuseTex = dTex;
			specularTex = defMaterial::getDefaultSpecularTex();
		}
		Material() {
			diffuseTex = defMaterial::getDefaultDiffuseTex();
			specularTex = defMaterial::getDefaultSpecularTex();
		}
		void bind(std::shared_ptr <Shader>shady, int matIndex, int& texUnit) {
			std::string temp = "material[" + std::to_string(matIndex) + "].albedoTex";
			diffuseTex->bind(texUnit);
			shady->setUniform1i(temp.c_str(), texUnit);
			diffuseTex->bind(texUnit);
			texUnit += 1;
			temp = "material[" + std::to_string(matIndex) + "].specularTex";
			specularTex->bind(texUnit);
			shady->setUniform1i(temp.c_str(), texUnit);
			specularTex->bind(texUnit);
			texUnit += 1;
		}

	};
}

