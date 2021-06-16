#pragma once
#include"CustomMesh.h"
gameEngine::CustomMesh* gameEngine::CustomMesh::customM;


gameEngine::CustomMesh::CustomMesh() {
	std::vector<float> vertices_box = {
		-0.5f, 0.5f, 0.f, 1.f,
		-0.5f,-0.5f, 0.f, 0.f,
		 0.5f,-0.5f, 1.f, 0.f,
		 0.5f, 0.5f, 1.f, 1.f
	};
	std::vector<unsigned int> indVert = {
		2,1,0,
		3,2,0
	};
	quad = new Mesh(vertices_box, indVert, Mesh::dataDistribution::P2F | Mesh::dataDistribution::T2F);

	std::vector<float> vertices = {
		// back face
		-1.f, -1.f, -1.f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		 1.f,  1.f, -1.f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		 1.f, -1.f, -1.f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
		 1.f,  1.f, -1.f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
		-1.f, -1.f, -1.f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
		-1.f,  1.f, -1.f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
		// front face	   
		-1.f, -1.f,  1.f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		 1.f, -1.f,  1.f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
		 1.f,  1.f,  1.f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		 1.f,  1.f,  1.f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
		-1.f,  1.f,  1.f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
		-1.f, -1.f,  1.f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
		// left face	 
		-1.f,  1.f,  1.f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		-1.f,  1.f, -1.f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
		-1.f, -1.f, -1.f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.f, -1.f, -1.f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
		-1.f, -1.f,  1.f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.f,  1.f,  1.f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
		// right face	 
		 1.f,  1.f,  1.f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.f, -1.f, -1.f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.f,  1.f, -1.f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
		 1.f, -1.f, -1.f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
		 1.f,  1.f,  1.f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
		 1.f, -1.f,  1.f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
		// bottom face	
		-1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		 1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
		 1.f, -1.f,  1.f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		 1.f, -1.f,  1.f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
		-1.f, -1.f,  1.f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
		-1.f, -1.f, -1.f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
		// top face	
		-1.f,  1.f, -1.f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		 1.f,  1.f , 1.f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		 1.f,  1.f, -1.f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
		 1.f,  1.f,  1.f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
		-1.f,  1.f, -1.f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
		-1.f,  1.f,  1.f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
	};
	std::vector<unsigned int> empIndex;
	Cube = new Mesh(vertices, empIndex, Mesh::dataDistribution::P3F | Mesh::dataDistribution::N3F | Mesh::dataDistribution::T2F);
}

gameEngine::CustomMesh* gameEngine::CustomMesh::initCustomMesh() {
	if (customM == NULL) {
		customM = new CustomMesh();
	}
	return customM;
}
gameEngine::Mesh* gameEngine::CustomMesh::getCustomCube() {
	return customM->Cube;
}
gameEngine::Mesh* gameEngine::CustomMesh::getCustomQuad() {
	return customM->quad;
}
void gameEngine::CustomMesh::deleteCustomMesh() {
	delete customM;
}