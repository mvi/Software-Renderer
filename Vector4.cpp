#include "stdafx.h"
#include "Vector4.h"

Vector4::Vector4(float x, float y, float z, float w)
{
	Vector4::x = x;
	Vector4::y = y;
	Vector4::z = z;
	Vector4::w = w;
}
Vector4::Vector4(Vector3 vector1, float w)
{
	Vector4::x = vector1.x;
	Vector4::y = vector1.y;
	Vector4::z = vector1.z;
	Vector4::w = w;
}
Vector4::Vector4(void)
{
}

Vector4::~Vector4(void)
{
}
