#pragma once

class Vector2
{
public:
	Vector2(void);
	Vector2(float, float);
	~Vector2(void);

	float x;   
	float y;

	static Vector2 Multiply(Vector2, float);
};
