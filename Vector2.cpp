#include "stdafx.h"
#include "Vector2.h"

Vector2::Vector2(float x, float y)
{
	Vector2::x = x;
	Vector2::y = y;
}

Vector2::Vector2(void)
{
}

Vector2::~Vector2(void)
{
}

Vector2 Vector2::Multiply(Vector2 vector1, float scale)
{
	vector1.x *= scale;
	vector1.y *= scale;
	return vector1;
}