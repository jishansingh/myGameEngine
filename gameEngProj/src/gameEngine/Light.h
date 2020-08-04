#pragma once

#include"libs.h"
#include"Core.h"
namespace gameEngine {


	class FUN_API Light {
		std::vector<glm::vec3> positions;
		std::vector<glm::vec3> color;
		std::vector<float> power;
		Light(const bool draw = false) {
		}


	};
}

