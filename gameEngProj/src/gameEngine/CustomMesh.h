#pragma once
#include"Mesh.h"

namespace gameEngine {
	class FUN_API CustomMesh {
	public:
		Mesh* Cube;
		Mesh* quad;
		static CustomMesh* customM;
		CustomMesh();

		static CustomMesh* initCustomMesh();
		static Mesh* getCustomCube();
		static Mesh* getCustomQuad();
		static void deleteCustomMesh();
	};
}

