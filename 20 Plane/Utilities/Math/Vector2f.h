#pragma once

#include <cmath>
//--------------------------------------------------------------------

class Vector2f
{
public:

	//	vector elements.
	union
	{
		struct
		{
			float x;
			float y;
		};

		float v[2];
	};


	/*
		Constructors.
	*/
	Vector2f()
	//	:	x(0.0f),			//	Remove default initialization
	//		y(0.0f)
	{
		//	Empty
	}

	Vector2f(const Vector2f &v)
		:	x(v.x),
			y(v.y)
	{
		//	Empty
	}

	Vector2f(float vX, float vY)
		:	x(vX),
			y(vY)
	{
		//	Empty
	}

	Vector2f(const float * const xy)
		:	x(xy[0]),
			y(xy[1])
	{
		//	Empty
	}

	/*
		Standard functions.
	*/

	inline const float * const get() const
	{
		return v;
	}
	
	/*
		Set vector by value
	*/
	inline void set(float x, float y)
	{
		v[0] = x;
		v[1] = y;
	}

	/*
		Set vector by array
	*/
	inline void set(const float * const xy)
	{
		x = xy[0];
		y = xy[1];
	}

	/*
		Update vector by vactor
	*/
	inline void set(const Vector2f &v)
	{
		x = v.x;
		y = v.y;
	}
	
	/*
		Update vector by value
	*/
	inline void update(float x, float y)
	{
		v[0] += x;
		v[1] += y;
	}

	/*
		Update vector by array
	*/
	inline void update(const float * const xy)
	{
		x += xy[0];
		y += xy[1];
	}

	/*
		Update vector by vactor
	*/
	inline void update(const Vector2f &v)
	{
		x += v.x;
		y += v.y;
	}
	
	/*
		This function is called to set the vector to a null vector.
	*/
	inline void null()
	{
		x = 0.0f;
		y = 0.0f;
	}
	
	/*
		This function is called to check the vector is a null vector.
	*/
	inline bool isNull() const
	{
		return (x == 0 && y == 0);
	}
	
	/*
		This function is called to normalize the vector.
	*/
	inline void normalise()
	{
		float r = length();
		if (r != 0.0f) 
		{
			x /= r;
			y /= r;
		}
		else
		{
			null();
		}
	}
	
	/*
		This function is called to get the length of vector in square format.
	*/
	inline float lengthSq() const
	{
		return (x * x + y * y);
	}
	
	/*
		This function is called to get the length of vector.
	*/
	inline float length() const
	{
		return sqrt(lengthSq());
	}

	/*
		Unary arithmetic operators
	*/

	inline const Vector2f& operator += (const Vector2f &v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	inline const Vector2f& operator -= (const Vector2f &v)
	{
		x -= v.x;
		y -= v.y;
		return *this;
	}

	inline const Vector2f& operator *= (float v)
	{
		x *= v;
		y *= v;
		return *this;
	}

	inline const Vector2f& operator /= (float v)
	{
		x /= v;
		y /= v;
		return *this;
	}

	inline const Vector2f& operator = (float v)
	{
		x = v;
		y = v;
		return *this;
	}
	
	/*
		Operator for retrieving data
	*/

	inline const float& operator[](size_t i) const 
	{
		if (i > 2) i = 1;
		return v[i];
	}
	
	/*
		Operator for modifying data
	*/
	inline float& operator[](size_t i) 
	{
		if (i > 2) i = 1;
		return v[i];
	}
	
	/*
		Check equality to target vector
	*/
	inline bool operator == (const Vector2f &v) const
	{		
		return ((x == v.x) && (y == v.y));
	}
	
	/*
		Check inequality to target vector
	*/
	inline bool operator != (const Vector2f &v) const
	{		
		return !(*this == v);
	}
};
//--------------------------------------------------------------------

//	Global null vector
static Vector2f g_nullVector2f(0.0f, 0.0f);
//--------------------------------------------------------------------

/*
	Arithmetic operators.
*/

// operators +
inline Vector2f operator + (const Vector2f &v1, const Vector2f &v2)
{
	return Vector2f(v1.x + v2.x, v1.y + v2.y);
}
//--------------------------------------------------------------------

// operators -
inline Vector2f operator - (const Vector2f &v1, const Vector2f &v2)
{
	return Vector2f(v1.x - v2.x, v1.y - v2.y);
}
//--------------------------------------------------------------------

// operators *
inline Vector2f operator * (const Vector2f &v, const float &i)
{
	return Vector2f(v.x * i, v.y * i);
}
//--------------------------------------------------------------------

inline Vector2f operator * (const float &i, const Vector2f &v)
{
	return Vector2f(i * v.x, i * v.y);
}
//--------------------------------------------------------------------

// operators /
inline Vector2f operator / (const Vector2f &v, const float &i)
{
	return Vector2f(v.x / i, v.y / i);
}
//--------------------------------------------------------------------
	
inline Vector2f operator / (const float &i, const Vector2f &v)
{
	return Vector2f(i / v.x, i / v.y);
}
//--------------------------------------------------------------------

/*
	Unary operators.
*/
inline Vector2f operator - (const Vector2f &v)
{
	return Vector2f(-v.x, -v.y);
}
//--------------------------------------------------------------------
	
inline Vector2f operator ++ (const Vector2f &v)
{
	return Vector2f(v.x + 1, v.y + 1);
}
//--------------------------------------------------------------------
	
inline Vector2f operator -- (const Vector2f &v)
{
	return Vector2f(v.x - 1, v.y - 1);
}
//--------------------------------------------------------------------

/*
	This function is called to get the length of vector in square format.
*/
inline float lengthSq(const Vector2f &v)
{
	return (v.x * v.x + v.y * v.y);
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the length of vector.
*/
inline float length(const Vector2f &v)
{
	return sqrt(lengthSq(v));
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the distance from target vector in square format.
*/
//	Change to non member function
inline float distanceSq(const Vector2f &v1, const Vector2f &v2)
{
	return lengthSq(v1 - v2);
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the distance from target vector.
*/
inline float distance(const Vector2f &v1, const Vector2f &v2)
{
	return sqrt(distanceSq(v1, v2));
}
//--------------------------------------------------------------------

/*
	This function is called to normalize the target vector.
*/
inline Vector2f normalise(const Vector2f &v)
{
	float r = v.length();
	if (r != 0) 
		return Vector2f(v.x / r, v.y / r);

	return g_nullVector2f;
}
//--------------------------------------------------------------------

/*
	This function is called to calculate the dot product to a target vector.
*/

inline float dot(const Vector2f &v1, const Vector2f &v2)
{
	return v1.x * v2.x + v1.y * v2.y;
}
//--------------------------------------------------------------------

/*
	This function is called to calculate angle between vectors
*/

inline float getAngle(const Vector2f &v1, const Vector2f &v2) 
{
	// To calculate the angle between 2 vectors
	// cos(theta) = p . q / |p| * |q|

	// calculate p dot q
	float pDotQ = dot(v1, v2);

	// length of p multiply with length of q
	float lengths = v1.length() * v2.length();
	if (lengths < 0.0001f) lengths = 0.1f;
	//else lengths = sqrt(lengths);

	// calculate the theta value
	float value = pDotQ / lengths;
	if (value > 1.0f) value = 1.0f;
	else if (value < -1.0f) value = -1.0f;
				
	return acos(value);
}
//--------------------------------------------------------------------