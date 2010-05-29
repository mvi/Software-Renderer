#pragma once
#include "Structs.h"
#include "Mesh.h"
#include <vector>
using namespace std;
class Model
{
public:
	Model(char*);
	Model(void);
	~Model(void);	

	vector<Mesh> meshes;
	//	vector<VECTOR3> vertexBuffer;
	//vector<VECTOR3> normalBuffer;
	//vector<VECTOR3> texturecoordinateBuffer;
	//vector<INT3> indexBuffer;

private:


};
