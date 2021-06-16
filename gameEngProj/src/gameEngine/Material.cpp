#pragma once
#include"Material.h"
std::shared_ptr <gameEngine::defMaterial> gameEngine::defMaterial::defaultMat;

gameEngine::defMaterial::defMaterial() {
	char som[] = { 255,0,0 };
	diffuseTex = std::make_shared<Texture>(*new Texture(GL_TEXTURE_2D, GL_SRGB, GL_RGBA, GL_UNSIGNED_BYTE, 1, 1, som));
	specularTex = std::make_shared<Texture>(*new Texture(GL_TEXTURE_2D, GL_SRGB, GL_RGBA, GL_UNSIGNED_BYTE, 1, 1, som));
}
std::shared_ptr <gameEngine::defMaterial> gameEngine::defMaterial::initDefMat() {
	if (!defaultMat) {
		defaultMat = std::make_shared<defMaterial>(*new defMaterial());
	}
	return defaultMat;
}
std::shared_ptr <gameEngine::Texture> gameEngine::defMaterial::getDefaultDiffuseTex() {
	return initDefMat()->diffuseTex;
}
std::shared_ptr <gameEngine::Texture> gameEngine::defMaterial::getDefaultSpecularTex() {
	return initDefMat()->specularTex;
}



gameEngine::Material::Material(Texture* dTex, Texture* sTex) {
	if (dTex) {
		diffuseTex = std::make_shared<Texture>(*dTex);
	}
	else {
		diffuseTex = defMaterial::initDefMat()->getDefaultDiffuseTex();
	}
	if (sTex) {
		specularTex = std::make_shared<Texture>(*sTex);
	}
	else {
		specularTex = defMaterial::initDefMat()->getDefaultSpecularTex();
	}
}
gameEngine::Material::Material(std::shared_ptr <Texture>dTex) {
	diffuseTex = dTex;
	specularTex = defMaterial::initDefMat()->getDefaultSpecularTex();
}
gameEngine::Material::Material() {
	diffuseTex = defMaterial::initDefMat()->getDefaultDiffuseTex();
	specularTex = defMaterial::initDefMat()->getDefaultSpecularTex();
}
void gameEngine::Material::bind(std::shared_ptr <Shader>shady, int matIndex, int& texUnit) {
	std::string temp = "materialData[" + std::to_string(matIndex) + "].albedoTex";
	diffuseTex->bind(texUnit);
	shady->setUniform1i(temp.c_str(), texUnit);
	texUnit += 1;
	temp = "materialData[" + std::to_string(matIndex) + "].specularTex";
	specularTex->bind(texUnit);
	shady->setUniform1i(temp.c_str(), texUnit);
	texUnit += 1;
}


