#include "stdafx.h"
#include "Vector3.h"
#include <math.h>

Vector3::Vector3(float x, float y, float z)
{
	Vector3::x = x;
	Vector3::y = y;
	Vector3::z = z;
}

Vector3::Vector3(void)
{
}

Vector3::~Vector3(void)
{
}

Vector3 Vector3::Multiply(Vector3 vector1, float scale)
{
	vector1.x *= scale;
	vector1.y *= scale;
	vector1.z *= scale;
	return vector1;
}

Vector3 Vector3::Subtract(Vector3 vector1, Vector3 vector2)
{
	vector1.x -= vector2.x;
	vector1.y -= vector2.y;
	vector1.z -= vector2.z;
	return vector1;
}

float Vector3::LengthSquared(Vector3 vector1)
{
	return pow(vector1.x,2) + pow(vector1.y,2) + pow(vector1.z,2);
}

float Vector3::Length(Vector3 vector1)
{
	return sqrtf(LengthSquared(vector1));
}

Vector3 Vector3::Normalize(Vector3 vector1)
{
	float length = Length(vector1);
	if(length == 0)
		return Vector3(0,0,0);
	else
		return Multiply(vector1, 1/length);
}

float Vector3::Dot(Vector3 vector1, Vector3 vector2)
{
	return vector1.x * vector2.x + vector1.y * vector2.y + vector1.z * vector2.z;
}
Vector3 Vector3::Cross(Vector3 vector1, Vector3 vector2)
{
	Vector3 result;
	result.x = vector1.y * vector2.z - vector2.y * vector1.z;
    result.y = vector1.z * vector2.x - vector2.z * vector1.x;
    result.z = vector1.x * vector2.y - vector2.x * vector1.y;

	return result;
}