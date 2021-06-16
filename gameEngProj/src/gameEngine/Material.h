#pragma once
#include"libs.h"
#include"Texture.h"
#include"Shader.h"
namespace gameEngine {

	class FUN_API defMaterial {
	public:
		std::shared_ptr <Texture>diffuseTex;
		std::shared_ptr <Texture>specularTex;
		defMaterial();
		static std::shared_ptr <defMaterial> defaultMat;
		static std::shared_ptr <defMaterial> initDefMat();
		static std::shared_ptr <Texture> getDefaultDiffuseTex();
		static std::shared_ptr <Texture> getDefaultSpecularTex();
	};

	class FUN_API Material {
	public:
		std::shared_ptr <Texture>diffuseTex;
		std::shared_ptr <Texture>specularTex;
		glm::vec3 diffuseColor;
		glm::vec3 specColor;
		float roughness = 0.5f;
		Material(Texture* dTex, Texture* sTex);
		Material(std::shared_ptr <Texture>dTex);
		Material();
		void bind(std::shared_ptr <Shader>shady, int matIndex, int& texUnit);

	};
}

