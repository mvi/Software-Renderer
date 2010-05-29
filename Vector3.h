#pragma once

class Vector3
{
public:
	Vector3(void);
	Vector3(float, float, float);
	~Vector3(void);

	float x;   
	float y;
	float z;

	static Vector3 Multiply(Vector3, float);
	static Vector3 Subtract(Vector3, Vector3);
	static float Length(Vector3);
	static float LengthSquared(Vector3);
	static Vector3 Normalize(Vector3);
	static float Dot(Vector3,Vector3);
	static Vector3 Cross(Vector3,Vector3);

private:


};
