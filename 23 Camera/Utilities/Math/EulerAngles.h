#pragma once

#include "Radian.h"
//--------------------------------------------------------------------

/*
	Sora specifies Euler Angles in radian,
	to be consistent with C++ trigonometry functions.
*/

class EulerAngles
{
public:

	union
	{
		//	For easier access
		struct
		{
			float x, y, z;
		};
		struct
		{
			Radian p, h, b;
		};
	};

	/*
		Constructors.
	*/
	EulerAngles()
	{
		//	Empty
	}

	/*
		Constructors.
	*/
	EulerAngles(float x, float y, float z)
		:	p(x),
			h(y),
			b(z)
	{
		//	Empty
	}
		
	/*
		This function is called to set the Euler angles to null.
	*/
	inline void null()
	{
		p = h = b = 0.0f;
	}

	/*
		This function is called to rotate the Euler angles about the x-axis.
	*/
	inline void rotateX(float theta)
	{
		p = theta;
	}

	/*
		This function is called to rotate the Euler angles about the y-axis.
	*/
	inline void rotateY(float theta)
	{
		h = theta;
	}

	/*
		This function is called to rotate the Euler angles about the z-axis.
	*/
	inline void rotateZ(float theta)
	{
		b = theta;
	}

	/*
		This function is called to rotate the Euler angles.
	*/
	inline void rotate(float aX, float aY, float aZ)
	{
		p = aX;
		h = aY;
		b = aZ;
	}

	/*
		This function is called to increment the Euler angles about the x-axis.
	*/
	inline void incX(float theta)
	{
		p += theta;
	}

	/*
		This function is called to increment the Euler angles about the y-axis.
	*/
	inline void incY(float theta)
	{
		h += theta;
	}

	/*
		This function is called to increment the Euler angles about the z-axis.
	*/
	inline void incZ(float theta)
	{
		b += theta;
	}

	/*
		This function is called to get the heading angle.
	*/
	inline float getHeading() const
	{
		return h.get();
	}

	/*
		This function is called to get the pitch angle.
	*/
	inline float getPitch() const
	{
		return p.get();
	}

	/*
		This function is called to get the bank angle.
	*/
	inline float getBank() const
	{
		return b.get();
	}

};
//--------------------------------------------------------------------