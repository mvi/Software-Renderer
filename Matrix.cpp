#include "stdafx.h"
#include "Matrix.h"
#include <math.h>

Matrix::Matrix(void)
{
}

Matrix::Matrix(float m11, float m12, float m13, float m14,
		float m21, float m22, float m23, float m24,
		float m31, float m32, float m33, float m34,
		float m41, float m42, float m43, float m44)
{
	Matrix::m11 = m11;
	Matrix::m12 = m12;
	Matrix::m13 = m13;
	Matrix::m14 = m14;

	Matrix::m21 = m21;
	Matrix::m22 = m22;
	Matrix::m23 = m23;
	Matrix::m24 = m24;

	Matrix::m31 = m31;
	Matrix::m32 = m32;
	Matrix::m33 = m33;
	Matrix::m34 = m34;

	Matrix::m41 = m41;
	Matrix::m42 = m42;
	Matrix::m43 = m43;
	Matrix::m44 = m44;
}

Matrix::~Matrix(void)
{
	
}


Matrix Matrix::Multiply(Matrix matrix1, Matrix matrix2)
{
	Matrix result;
	result.m11 = matrix1.m11 * matrix2.m11 + matrix1.m12 * matrix2.m21 + matrix1.m13 * matrix2.m31 + matrix1.m14 * matrix2.m41;
	result.m12 = matrix1.m11 * matrix2.m12 + matrix1.m12 * matrix2.m22 + matrix1.m13 * matrix2.m32 + matrix1.m14 * matrix2.m42;
	result.m13 = matrix1.m11 * matrix2.m13 + matrix1.m12 * matrix2.m23 + matrix1.m13 * matrix2.m33 + matrix1.m14 * matrix2.m43;
	result.m14 = matrix1.m11 * matrix2.m14 + matrix1.m12 * matrix2.m24 + matrix1.m13 * matrix2.m34 + matrix1.m14 * matrix2.m44;

	result.m21 = matrix1.m21 * matrix2.m11 + matrix1.m22 * matrix2.m21 + matrix1.m23 * matrix2.m31 + matrix1.m24 * matrix2.m41;
	result.m22 = matrix1.m21 * matrix2.m12 + matrix1.m22 * matrix2.m22 + matrix1.m23 * matrix2.m32 + matrix1.m24 * matrix2.m42;
	result.m23 = matrix1.m21 * matrix2.m13 + matrix1.m22 * matrix2.m23 + matrix1.m23 * matrix2.m33 + matrix1.m24 * matrix2.m43;
	result.m24 = matrix1.m21 * matrix2.m14 + matrix1.m22 * matrix2.m24 + matrix1.m23 * matrix2.m34 + matrix1.m24 * matrix2.m44;

	result.m31 = matrix1.m31 * matrix2.m11 + matrix1.m32 * matrix2.m21 + matrix1.m33 * matrix2.m31 + matrix1.m34 * matrix2.m41;
	result.m32 = matrix1.m31 * matrix2.m12 + matrix1.m32 * matrix2.m22 + matrix1.m33 * matrix2.m32 + matrix1.m34 * matrix2.m42;
	result.m33 = matrix1.m31 * matrix2.m13 + matrix1.m32 * matrix2.m23 + matrix1.m33 * matrix2.m33 + matrix1.m34 * matrix2.m43;
	result.m34 = matrix1.m31 * matrix2.m14 + matrix1.m32 * matrix2.m24 + matrix1.m33 * matrix2.m34 + matrix1.m34 * matrix2.m44;

	result.m41 = matrix1.m41 * matrix2.m11 + matrix1.m42 * matrix2.m21 + matrix1.m43 * matrix2.m31 + matrix1.m44 * matrix2.m41;
	result.m42 = matrix1.m41 * matrix2.m12 + matrix1.m42 * matrix2.m22 + matrix1.m43 * matrix2.m32 + matrix1.m44 * matrix2.m42;
	result.m43 = matrix1.m41 * matrix2.m13 + matrix1.m42 * matrix2.m23 + matrix1.m43 * matrix2.m33 + matrix1.m44 * matrix2.m43;
	result.m44 = matrix1.m41 * matrix2.m14 + matrix1.m42 * matrix2.m24 + matrix1.m43 * matrix2.m34 + matrix1.m44 * matrix2.m44;

	return result;
}

Vector3 Matrix::Multiply(Matrix matrix1, Vector3 vector1)
{
	return Vector3(matrix1.m11 * vector1.x + matrix1.m12 * vector1.y + matrix1.m13 * vector1.z,
		matrix1.m21 * vector1.x + matrix1.m22 * vector1.y + matrix1.m23 * vector1.z,
		matrix1.m31 * vector1.x + matrix1.m32 * vector1.y + matrix1.m33 * vector1.z);
}
Vector4 Matrix::Multiply(Matrix matrix1, Vector4 vector1)
{
	return Vector4(
		matrix1.m11 * vector1.x + matrix1.m12 * vector1.y + matrix1.m13 * vector1.z + matrix1.m14 * vector1.w,
		matrix1.m21 * vector1.x + matrix1.m22 * vector1.y + matrix1.m23 * vector1.z + matrix1.m24 * vector1.w,
		matrix1.m31 * vector1.x + matrix1.m32 * vector1.y + matrix1.m33 * vector1.z + matrix1.m34 * vector1.w,
		matrix1.m41 * vector1.x + matrix1.m42 * vector1.y + matrix1.m43 * vector1.z + matrix1.m44 * vector1.w);
}
Vector4 Matrix::MultiplyB(Matrix matrix1, Vector3 vector1)
{
    return Vector4((vector1.x * matrix1.m11) + (vector1.y * matrix1.m21) + (vector1.z * matrix1.m31) + matrix1.m41,
                        (vector1.x * matrix1.m12) + (vector1.y * matrix1.m22) + (vector1.z * matrix1.m32) + matrix1.m42,
                        (vector1.x * matrix1.m13) + (vector1.y * matrix1.m23) + (vector1.z * matrix1.m33) + matrix1.m43,
                        (vector1.x * matrix1.m14) + (vector1.y * matrix1.m24) + (vector1.z * matrix1.m34) + matrix1.m44);

}
Vector4 Matrix::MultiplyB(Matrix matrix1, Vector4 vector1)
{
	return Vector4((vector1.x * matrix1.m11) + (vector1.y * matrix1.m21) + (vector1.z * matrix1.m31) + (vector1.w * matrix1.m41),
                                 (vector1.x * matrix1.m12) + (vector1.y * matrix1.m22) + (vector1.z * matrix1.m32) + (vector1.w * matrix1.m42),
                                 (vector1.x * matrix1.m13) + (vector1.y * matrix1.m23) + (vector1.z * matrix1.m33) + (vector1.w * matrix1.m43),
                                 (vector1.x * matrix1.m14) + (vector1.y * matrix1.m24) + (vector1.z * matrix1.m34) + (vector1.w * matrix1.m44));
}


Matrix Matrix::CreateRotationX(float rotation)
{
	return Matrix(	1,0,0,0,
					0,cos(rotation),sin(rotation),0,
					0,-sin(rotation),cos(rotation),0,
					0,0,0,1);
}
//TODO Ensure that X and Y functions are right way round
Matrix Matrix::CreateRotationY(float rotation)
{
	return Matrix(	cosf(rotation),0,-sinf(rotation),0,
					0,1,0,0,
					sinf(rotation),0,cosf(rotation),0,
					0,0,0,1);
}
Matrix Matrix::CreateRotationZ(float rotation)
{
	return Matrix(	cosf(rotation),sinf(rotation),0,0,
					-sinf(rotation),cos(rotation),0,0,
					0,0,1,0,
					0,0,0,1);
}
Matrix Matrix::CreateTranslation(float x, float y, float z)
{
	return Matrix(	1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					x,y,z,1);
}
Matrix Matrix::CreateScale(float x, float y, float z)
{
	return Matrix(	x,0,0,0,
					0,y,0,0,
					0,0,z,0,
					0,0,0,1);
}
Matrix Matrix::CreateIdentity()
{
	return Matrix(	1,0,0,0,
					0,1,0,0,
					0,0,1,0,
					0,0,0,1);
}
//Builds a left-handed perspective projection matrix based on a field of view.
Matrix Matrix::CreatePerspectiveFieldOfView(float fieldofview, float aspectratio, float nearplane, float farplane)
{
	//float yScale  = cot(fovY/2)
	float yScale  = 1 / tan(fieldofview/2);
	float xScale = yScale / aspectratio;

	return Matrix(	xScale,0,0,0,
					0,yScale,0,0,
					0,0,farplane/(farplane-nearplane),1,
					0,0,-nearplane*farplane/(farplane-nearplane),0);
}

Matrix Matrix::CreateLookAt(Vector3 eye, Vector3 target, Vector3 up)
{
	
	Vector3 zaxis = Vector3::Normalize(Vector3::Subtract(target, eye));
	Vector3 xaxis = Vector3::Normalize(Vector3::Cross(up, zaxis));
	Vector3 yaxis = Vector3::Cross(zaxis, xaxis);
    
	 return Matrix(	 xaxis.x,           yaxis.x,           zaxis.x,          0,
					 xaxis.y,           yaxis.y,           zaxis.y,          0,
					 xaxis.z,           yaxis.z,           zaxis.z,          0,
					 -Vector3::Dot(xaxis, eye),  -Vector3::Dot(yaxis, eye),  -Vector3::Dot(zaxis, eye), 1);
}