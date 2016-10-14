#pragma once

#include <cmath>
//--------------------------------------------------------------------

class Vector3f
{
public:

	//	vector elements.
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};

		float v[3];
	};


	/*
		Constructors.
	*/
	Vector3f()
	//	:	x(0.0f),			//	Remove default initialization
	//		y(0.0f)
	{
		//	Empty
	}

	Vector3f(const Vector3f &v)
		:	x(v.x),
			y(v.y),
			z(v.z)
	{
		//	Empty
	}

	Vector3f(float vX, float vY, float vZ)
		:	x(vX),
			y(vY),
			z(vZ)
	{
		//	Empty
	}

	Vector3f(const float * const xyz)
		:	x(xyz[0]),
			y(xyz[1]),
			z(xyz[2])
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
	inline void set(float x, float y, float z)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
	}

	/*
		Set vector by array
	*/
	inline void set(const float * const xyz)
	{
		x = xyz[0];
		y = xyz[1];
		z = xyz[2];
	}

	/*
		Update vector by vactor
	*/
	inline void set(const Vector3f &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
	}
	
	/*
		Update vector by value
	*/
	inline void update(float x, float y, float z)
	{
		v[0] += x;
		v[1] += y;
		v[2] += z;
	}

	/*
		Update vector by array
	*/
	inline void update(const float * const xyz)
	{
		x += xyz[0];
		y += xyz[1];
		z += xyz[2];
	}

	/*
		Update vector by vactor
	*/
	inline void update(const Vector3f &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}
	
	/*
		This function is called to set the vector to a null vector.
	*/
	inline void null()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
	}
	
	/*
		This function is called to check the vector is a null vector.
	*/
	inline bool isNull() const
	{
		return (x == 0 && y == 0 && z == 0);
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
			z /= r;
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
		return (x * x + y * y + z * z);
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

	inline const Vector3f& operator += (const Vector3f &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		return *this;
	}

	inline const Vector3f& operator -= (const Vector3f &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		return *this;
	}

	inline const Vector3f& operator *= (float v)
	{
		x *= v;
		y *= v;
		z *= v;
		return *this;
	}

	inline const Vector3f& operator /= (float v)
	{
		x /= v;
		y /= v;
		z /= v;
		return *this;
	}

	inline const Vector3f& operator = (float v)
	{
		x = v;
		y = v;
		z = v;
		return *this;
	}
	
	/*
		Operator for retrieving data
	*/

	inline const float& operator[](size_t i) const 
	{
		if (i > 3) i = 2;
		return v[i];
	}
	
	/*
		Operator for modifying data
	*/
	inline float& operator[](size_t i) 
	{
		if (i > 3) i = 2;
		return v[i];
	}
	
	/*
		Check equality to target vector
	*/
	inline bool operator == (const Vector3f &v) const
	{		
		return ((x == v.x) && (y == v.y) && (z == v.z));
	}
	
	/*
		Check inequality to target vector
	*/
	inline bool operator != (const Vector3f &v) const
	{		
		return !(*this == v);
	}
};
//--------------------------------------------------------------------

//	Global null vector
static Vector3f g_nullVector3f(0.0f, 0.0f, 0.0f);
//--------------------------------------------------------------------

/*
	Arithmetic operators.
*/

// operators +
inline Vector3f operator + (const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}
//--------------------------------------------------------------------

// operators -
inline Vector3f operator - (const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}
//--------------------------------------------------------------------

// operators *
inline Vector3f operator * (const Vector3f &v, const float &i)
{
	return Vector3f(v.x * i, v.y * i, v.z * i);
}
//--------------------------------------------------------------------

	inline Vector3f operator * (const float &i, const Vector3f &v)
{
	return Vector3f(i * v.x, i * v.y, i * v.z);
}
//--------------------------------------------------------------------

// operators /
inline Vector3f operator / (const Vector3f &v, const float &i)
{
	return Vector3f(v.x / i, v.y / i, v.z / i);
}
//--------------------------------------------------------------------
	
inline Vector3f operator / (const float &i, const Vector3f &v)
{
	return Vector3f(i / v.x, i / v.y, i / v.z);
}
//--------------------------------------------------------------------

/*
	Unary operators.
*/
inline Vector3f operator - (const Vector3f &v)
{
	return Vector3f(-v.x, -v.y, -v.z);
}
//--------------------------------------------------------------------
	
inline Vector3f operator ++ (const Vector3f &v)
{
	return Vector3f(v.x + 1, v.y + 1, v.z + 1);
}
//--------------------------------------------------------------------
	
inline Vector3f operator -- (const Vector3f &v)
{
	return Vector3f(v.x - 1, v.y - 1, v.z - 1);
}
//--------------------------------------------------------------------

/*
	This function is called to get the length of vector in square format.
*/
inline float lengthSq(const Vector3f &v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the length of vector.
*/
inline float length(const Vector3f &v)
{
	return sqrt(lengthSq(v));
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the distance from target vector in square format.
*/
//	Change to non member function
inline float distanceSq(const Vector3f &v1, const Vector3f &v2)
{
	return lengthSq(v1 - v2);
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the distance from target vector.
*/
inline float distance(const Vector3f &v1, const Vector3f &v2)
{
	return sqrt(distanceSq(v1, v2));
}
//--------------------------------------------------------------------

/*
	This function is called to normalize the target vector.
*/
inline Vector3f normalise(const Vector3f &v)
{
	float r = v.length();
	if (r != 0) 
		return Vector3f(v.x / r, v.y / r, v.z / r);

	return g_nullVector3f;
}
//--------------------------------------------------------------------

/*
	This function is called to calculate the dot product to a target vector.
*/

inline float dot(const Vector3f &v1, const Vector3f &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}
//--------------------------------------------------------------------

/*
	This function is called to calculate the cross product to a target vector.
*/

inline Vector3f cross(const Vector3f &v1, const Vector3f &v2)
{
	return Vector3f(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}
//--------------------------------------------------------------------

/*
	This function is called to calculate angle between vectors
*/

inline float getAngle(const Vector3f &v1, const Vector3f &v2) 
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