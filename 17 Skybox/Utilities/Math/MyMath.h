#pragma once

#include <cmath>
//--------------------------------------------------------------------

#define EPSILON 1E-6
//--------------------------------------------------------------------

const float FullDegree = 360.0f;
const float HalfDegree = 180.0f;

const float PI = 3.141592654f;
const float TwoPI = 6.283185307f;
const float OneDivPI = 0.318309886f;
const float PIDivTwo = 1.570796327f;
const float PIDivFour = 0.785398163f;

const float RadianToDegree = HalfDegree / PI;
const float DegreeToRadian = PI / HalfDegree;
//--------------------------------------------------------------------

inline float toRadian(float degree)
{
	return degree * DegreeToRadian;
}
//--------------------------------------------------------------------

inline float toDegree(float radian)
{
	return radian * RadianToDegree;
}
//--------------------------------------------------------------------

template<class T>
inline T minValue(const T& value1, const T& value2)
{
	(value1 > value2) ? return value2 : return value1;
}
//--------------------------------------------------------------------

template<class T>
inline T maxValue(const T& value1, const T& value2)
{
	(value1 > value2) ? return value1 : return value2;
}
//--------------------------------------------------------------------