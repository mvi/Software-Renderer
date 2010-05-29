#pragma once
#include "Vector3.h"

class Camera
{
public:
	Camera(void);
	Camera(Vector3,Vector3,Vector3);
	~Camera(void);

	Vector3 eye,target,up;
};

