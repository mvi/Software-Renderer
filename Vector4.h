#pragma once
#include "Vector3.h"
class Vector4
{
public:
	Vector4(float,float,float,float);
	Vector4(Vector3,float);
	Vector4(void);
	~Vector4(void);

	float x,y,z,w;	
};
