#pragma once

#include "Vector3f.h"
#include "EulerAngles.h"
//--------------------------------------------------------------------

class Quaternion
{
public:

	float w, x, y, z;

	/*
		Constructors.
	*/
	Quaternion()
	{
		//	Empty
	}

	/*
		Constructors.
	*/
	Quaternion(float qW, float qX, float qY, float qZ)
		:	w(qW),
			x(qX),
			y(qY),
			z(qZ)
	{
		//	Empty
	}
		
	/*
		This function is called to set the quaternion to null.
	*/
	inline void null()
	{
		w = x = y = z = 0.0f;
	}
		
	/*
		This function is called to set the quaternion to identity.
	*/
	inline void identity()
	{
		w = 1.0f;
		x = y = z = 0.0f;
	}

};
//--------------------------------------------------------------------

inline Quaternion identity()
{
	return Quaternion(1.0f, 0.0f, 0.0f, 0.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to rotate a quaternion about the x-axis.
	theta in radian.
*/
inline Quaternion quaternionRotationX(float theta)
{
	float t2 = theta / 2.0f;
	return Quaternion(cos(t2), sin(t2), 0.0f, 0.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to rotate a quaternion about the y-axis.
	theta in radian.
*/
inline Quaternion quaternionRotationY(float theta)
{
	float t2 = theta / 2.0f;
	return Quaternion(cos(t2), 0.0f, sin(t2), 0.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to rotate a quaternion about the z-axis.
	theta in radian.
*/
inline Quaternion quaternionRotationZ(float theta)
{
	float t2 = theta / 2.0f;
	return Quaternion(cos(t2), 0.0f, 0.0f, sin(t2));
}
//--------------------------------------------------------------------

/*
	This function is called to rotate a quaternion about the arbitrary axis.
*/
inline Quaternion quaternionRotationArbitrary(float theta, float x, float y, float z)
{
	float t2 = theta / 2.0f, s = sin(t2);
	return Quaternion(cos(t2), x * sin(t2), y * sin(t2), z * sin(t2));
}
//--------------------------------------------------------------------

/*
	This function is called to rotate a quaternion about the arbitrary axis.
*/
inline Quaternion quaternionRotationArbitrary(float theta, const Vector3f &axis)
{
	float t2 = theta / 2.0f, s = sin(t2);
	return Quaternion(cos(t2), axis.x * sin(t2), axis.y * sin(t2), axis.z * sin(t2));
}
//--------------------------------------------------------------------

/*
	This function is called to construct a quaternion from Euler Angles.
*/
inline Quaternion quaternionFromEulerAngles(float heading, float pitch, float bank)
{
	float h2 = heading / 2.0f, p2 = pitch / 2.0f, b2 = bank / 2.0f,
			cH = cos(h2), cP = cos(p2), cB = cos(b2),
			sH = sin(h2), sP = sin(p2), sB = sin(b2),
			cPcB = cP * cB, sPsB = sP * sB, cPsB = cP * sB, sPcB = sP * cB;
	return Quaternion(	cH * cPcB + sH * sPsB,
						cH * sPcB + sH * cPsB,
						sH * cPcB - cH * sPsB,
						cH * cPsB - sH * sPcB
						);
}
//--------------------------------------------------------------------

/*
	This function is called to construct a quaternion from Euler Angles.
*/
inline Quaternion quaternionFromEulerAngles(const EulerAngles &a)
{
	return quaternionFromEulerAngles(a.y, a.x, a.z);
}
//--------------------------------------------------------------------

/*
	Operator * 
	to find the product q1q2.
*/
inline Quaternion operator * (const Quaternion &q1, const Quaternion &q2)
{
	return Quaternion(	q1.w * q2.w - q1.x * q2.x - q1.y * q2.y - q1.z * q2.z,
						q1.w * q2.x + q1.x * q2.w + q1.y * q2.z - q1.z * q2.y,
						q1.w * q2.y - q1.x * q2.z + q1.y * q2.w + q1.z * q2.x,
						q1.w * q2.z + q1.x * q2.y - q1.y * q2.x + q1.z * q2.w
						);
}
//--------------------------------------------------------------------