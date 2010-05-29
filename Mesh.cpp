#include "stdafx.h"
#include "Mesh.h"


using namespace std;

Mesh::Mesh(void)
{
}
Mesh::Mesh(char* name, vector<Vector3> vertexBuffer, vector<Vector3> normalBuffer, vector<Vector3> texturecoordinateBuffer, vector<INT3> indexBuffer)
{
	Mesh::name = name;
	Mesh::vertexBuffer = vertexBuffer;
	Mesh::normalBuffer = normalBuffer;
	Mesh::texturecoordinateBuffer = texturecoordinateBuffer;
	Mesh::indexBuffer = indexBuffer;
}

Mesh::~Mesh(void)
{
}
