#include <iostream>
#include <pch.h>
#include "DreamMath.h"

#include <cmath>

#ifdef WINDOWS
using namespace std;
#endif

float DreamMath::D_sin(float degrees)
{
	return sinf(degrees * DEG2RAD);
}

float DreamMath::D_cos(float degrees)
{
	return cosf(degrees * DEG2RAD);
}

float DreamMath::D_tan(float degrees)
{
	return tanf(degrees * DEG2RAD);
}

float DreamMath::D_asin(float num)
{
	if (num < -1 || num > 1)
	{
		printf("Not a valid number...\n");
		return -9999;
	}
	return asinf(num);
}

float DreamMath::D_acos(float num)
{
	if (num < -1 && num > 1)
	{
		printf("Not a valid number...\n");
		return -1;
	}
	return acosf(num);
}

float DreamMath::D_atan(float num)
{
	if (num < -1 && num > 1)
	{
		printf("Not a valid number...\n");
		return -1;
	}
	return atanf(num);
}

float DreamMath::D_abs(float num)
{
	return abs(num);
}

float DreamMath::D_pow(float num, float exp)
{
	return powf(num, exp);
}

float DreamMath::D_floor(float a)
{
	return floorf(a);
}

float DreamMath::D_ceiling(float a)
{
	return ceilf(a);
}

float DreamMath::D_rad2deg(float radians)
{
	return radians * RAD2DEG;
}

float DreamMath::D_deg2rad(float degrees)
{
	return degrees * DEG2RAD;
}

float DreamMath::D_sqrtf(float num)
{
	return sqrtf(num);
}

float DreamMath::D_truncf(float num)
{
	return truncf(num);
}

float DreamMath::D_round(float num, int decimal)
{
	float decimalMove = pow(10.0f, (float)decimal);

	int store = (int)(num * decimalMove + .5f);

	return ((float)store) / decimalMove;
}

float DreamMath::D_lerp(float A, float B, float time)
{
	return ((1 - time) * A) + (time * B);
}

float DreamMath::Dot(float *vec1, float *vec2, int size)
{
	float dot = 0;

	for (int i = 0; i < size; i++)
	{
		dot += vec1[i] * vec2[i];
	}

	return dot;
}

float DreamMath::Dot(float vec1[], float vec2[])
{
	float dot = 0;
	int size = (int)sizeof(vec1) / sizeof(float);

	for (int i = 0; i < size; i++)
	{
		dot += vec1[i] * vec2[i];
	}

	return dot;
}

float DreamMath::FixFloatingPointError(float num)
{
	float returnNum = num;
	float truncatedNum = truncf(returnNum);
	if (DreamMath::D_abs(returnNum - truncatedNum) < EPSILON)
	{
		returnNum = truncatedNum;
	}
	return returnNum;
}

DreamMath::DreamVector3 DreamMath::DreamVector3::operator*(DreamMath::DreamMatrix3X3 m)
{
	DreamVector3 newVec = DreamMath::DreamVector3();

	newVec.x = (this->x * m.matrix.data[0][0]) + (this->y * m.matrix.data[1][0]) + (this->z * m.matrix.data[2][0]);
	newVec.y = (this->x * m.matrix.data[0][1]) + (this->y * m.matrix.data[1][1]) + (this->z * m.matrix.data[2][1]);
	newVec.z = (this->x * m.matrix.data[0][2]) + (this->y * m.matrix.data[1][2]) + (this->z * m.matrix.data[2][2]);

	return newVec;
}
void DreamMath::DreamVector3::operator*=(DreamMath::DreamMatrix3X3 m)
{
	DreamMath::DreamVector3 newVec = DreamMath::DreamVector3();

	newVec.x = (this->x * m.matrix.data[0][0]) + (this->y * m.matrix.data[1][0]) + (this->z * m.matrix.data[2][0]);
	newVec.y = (this->x * m.matrix.data[0][1]) + (this->y * m.matrix.data[1][1]) + (this->z * m.matrix.data[2][1]);
	newVec.z = (this->x * m.matrix.data[0][2]) + (this->y * m.matrix.data[1][2]) + (this->z * m.matrix.data[2][2]);

	*this = newVec;
}

DreamMath::DreamVector4 DreamMath::DreamVector4::operator*(DreamMath::DreamMatrix4X4 m)
{
	DreamMath::DreamVector4 newVec = DreamMath::DreamVector4();

	newVec.x = (this->x * m.matrix.data[0][0]) + (this->y * m.matrix.data[1][0]) + (this->z * m.matrix.data[2][0]) + (this->w * m.matrix.data[3][0]);
	newVec.y = (this->x * m.matrix.data[0][1]) + (this->y * m.matrix.data[1][1]) + (this->z * m.matrix.data[2][1]) + (this->w * m.matrix.data[3][1]);
	newVec.z = (this->x * m.matrix.data[0][2]) + (this->y * m.matrix.data[1][2]) + (this->z * m.matrix.data[2][2]) + (this->w * m.matrix.data[3][2]);
	newVec.w = (this->x * m.matrix.data[0][3]) + (this->y * m.matrix.data[1][3]) + (this->z * m.matrix.data[2][3]) + (this->w * m.matrix.data[3][3]);

	return newVec;
}

void DreamMath::DreamVector4::operator*=(DreamMath::DreamMatrix4X4 m)
{
	DreamMath::DreamVector4 newVec = DreamMath::DreamVector4();

	newVec.x = (this->x * m.matrix.data[0][0]) + (this->y * m.matrix.data[1][0]) + (this->z * m.matrix.data[2][0]) + (this->w * m.matrix.data[3][0]);
	newVec.y = (this->x * m.matrix.data[0][1]) + (this->y * m.matrix.data[1][1]) + (this->z * m.matrix.data[2][1]) + (this->w * m.matrix.data[3][1]);
	newVec.z = (this->x * m.matrix.data[0][2]) + (this->y * m.matrix.data[1][2]) + (this->z * m.matrix.data[2][2]) + (this->w * m.matrix.data[3][2]);
	newVec.w = (this->x * m.matrix.data[0][3]) + (this->y * m.matrix.data[1][3]) + (this->z * m.matrix.data[2][3]) + (this->w * m.matrix.data[3][3]);

	*this = newVec;
}