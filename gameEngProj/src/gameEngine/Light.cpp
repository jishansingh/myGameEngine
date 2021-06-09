#pragma once
#include"Light.h"
#include"frameRenderObject.h"

gameEngine::LightObj::LightObj(glm::vec3 pos, glm::vec3 col) {
	position = new glm::vec3(pos);
	color = new glm::vec3(col);
}


gameEngine::Light::Light(std::vector<std::shared_ptr<Texture>>texBuffer, std::shared_ptr<Shader> lightShader, const bool draw) {
	gbuffer = texBuffer;
	shady = lightShader;
	std::shared_ptr <framebufferObject>fbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
	std::shared_ptr <framebufferObject>tempfbo = std::make_shared<framebufferObject>(*new framebufferObject(false));
	fro = std::make_shared<frameRenderObject>(*new frameRenderObject(fbo, CommonUsed::quadCam));
	drawFRO = std::make_shared<frameRenderObject>(*new frameRenderObject(tempfbo));
	fro->addRenderObj(CommonUsed::somQuad);
	drawLight = draw;
	if (draw) {
		cubeShader = std::make_shared <gameEngine::Shader>(*new gameEngine::Shader("simpleCubeVertexShader.glsl", "simpleCubeFragmentShader.glsl", ""));
		lightObj = CommonUsed::somCube;
		lightDraw = std::make_shared <instancedRenderer>(*new instancedRenderer(lightObj));
		drawFRO->addRenderObj(lightDraw);
	}
}
void gameEngine::Light::render(GLFWwindow* window, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam) {
	CommonUsed::somQuad->setShader(shady);
	fro->getFBO()->addTexture(resultTex, 0);
	for (int i = 0; i < gbuffer.size(); i++) {
		CommonUsed::somQuad->replaceTex(i, gbuffer[i]);
	}
	shady->setUniform1i("noOfLight", lightArr.size());
	for (int i = 0; i < lightArr.size(); i++) {
		std::string temp = "sceneLight[" + std::to_string(i) + "]";
		shady->setUniform3f((temp + ".position").c_str(), GL_FALSE, *lightArr[i]->position);
		shady->setUniform3f((temp + ".color").c_str(), GL_FALSE, *lightArr[i]->color);
	}
	sceneCam->sendCamPos(shady, "camPos");
	glDisable(GL_DEPTH_TEST);
	fro->render(window);
}
void gameEngine::Light::addNewLight(glm::vec3 pos, glm::vec3 col) {
	lightArr.push_back(std::shared_ptr<LightObj>(new LightObj(pos, col)));
}
void gameEngine::Light::update(int index) {
	lightDraw->updateDataIndex(index);

}
void gameEngine::Light::Draw(GLFWwindow* window, std::shared_ptr<Texture>depthTex, std::shared_ptr <Texture> resultTex, std::shared_ptr <Camera> sceneCam) {
	drawFRO->getFBO()->bind();
	CommonUsed::somCube->setShader(cubeShader);
	cubeShader->Use();
	CommonUsed::somCube->setSize(0.1f);
	drawFRO->getFBO()->setDepthTex(depthTex);
	drawFRO->getFBO()->addTexture(resultTex, 0);
	drawFRO->setCamera(sceneCam);
	drawFRO->getFBO()->check();
	glEnable(GL_DEPTH_TEST);
	if (drawLight) {
		lightDraw->getShader()->Use();
		lightDraw->updateModelMatrix();
		sceneCam->sendToShader(lightDraw->getShader());
		lightDraw->updateProjMatrix(window);
		lightDraw->Draw();
		//drawFRO->render(window);
	}
	glDisable(GL_DEPTH_TEST);
	CommonUsed::somCube->setSize(1.f);
	drawFRO->getFBO()->unBind();
}


