#pragma once
#include "Structs.h"
#include "Vector3.h"
#include "Vector4.h"
#include <vector>
using namespace std;
class Matrix
{
public:
	Matrix(void);
	Matrix(float,float,float,float,
		float,float,float,float,
		float,float,float,float,
		float,float,float,float);
	~Matrix(void);


	float m11, m12, m13, m14,
		m21, m22, m23, m24,
		m31, m32, m33, m34,
		m41, m42, m43, m44;

	static Matrix Multiply(Matrix, Matrix);
	static Vector3 Multiply(Matrix, Vector3);
	static Vector4 MultiplyB(Matrix, Vector3);
	static Vector4 MultiplyB(Matrix, Vector4);
	static Vector4 Multiply(Matrix, Vector4);

	static Matrix CreateTranslation(float,float,float);
	static Matrix CreateRotation(float,float,float);//TODO Implement
	static Matrix CreateRotation(Vector3);//TODO Implement
	static Matrix CreateRotationX(float);
	static Matrix CreateRotationY(float);
	static Matrix CreateRotationZ(float);
	static Matrix CreateScale(float,float,float);
	static Matrix CreateScale(Vector3);//TODO Implement
	static Matrix CreateIdentity(void);
	static Matrix CreatePerspectiveFieldOfView(float,float,float,float);
	static Matrix CreateLookAt(Vector3,Vector3,Vector3);
};
