#include "stdafx.h"
#include "Camera.h"

Camera::Camera(void)
{
}

Camera::Camera(Vector3 eye, Vector3 target, Vector3 up)
{
	Camera::eye = eye;
	Camera::target = target;
	Camera::up = up;
}


Camera::~Camera(void)
{
}
