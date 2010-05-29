#pragma once
#include "Structs.h"
#include <vector>
#include "Vector3.h"
using namespace std;
class Mesh
{
public:
	Mesh(void);
	Mesh(char*,vector<Vector3>,vector<Vector3>,vector<Vector3>,vector<INT3>);
	~Mesh(void);
//private:
	char* name;
	vector<Vector3> vertexBuffer;
	vector<Vector3> normalBuffer;
	vector<Vector3> texturecoordinateBuffer;
	vector<INT3> indexBuffer;
};
