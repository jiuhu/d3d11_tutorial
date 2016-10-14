#pragma once

#include "MyMath.h"
//--------------------------------------------------------------------

class Radian
{
public:

	/*
		Constructors.
	*/
	Radian()
		:	m_angle(0.0f)
	{
		//	Empty
	}

	/*
		Constructors.
	*/
	Radian(float radian)
		:	m_angle(radian)
	{
		//	Empty
	}
	
	/*
		Unary arithmetic operators
	*/

	inline const Radian& operator += (float a)
	{
		adjustment(m_angle);
		m_angle += a;
		return *this;
	}
	
	inline const Radian& operator -= (float a)
	{
		adjustment(m_angle);
		m_angle -= a;
		return *this;
	}
	
	inline const Radian& operator = (float a)
	{
		adjustment(a);
		return *this;
	}

	/*
		This function is called to get the bank m_angle.
	*/
	inline float get() const
	{
		return m_angle;
	}

	/*
		This function is called to get the angle in degree.
	*/
	inline float getDegree() const
	{
		return toDegree(m_angle);
	}

private:

	float m_angle;
	
	/*
		This function is called to adjust the radian in the bound of 0.0f <= radian <= 2PI.
	*/
	inline void adjustment(float a)
	{
		m_angle = (a <= 0.0f) ? TwoPI : (a >= TwoPI) ? 0.0f : a;
	}
};
//--------------------------------------------------------------------