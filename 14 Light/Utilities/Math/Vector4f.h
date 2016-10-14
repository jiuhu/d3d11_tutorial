#pragma once

#include <cmath>
//--------------------------------------------------------------------

class Vector4f
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
			float w;
		};

		float v[4];
	};


	/*
		Constructors.
	*/
	Vector4f()
	//	:	x(0.0f),			//	Remove default initialization
	//		y(0.0f)
	{
		//	Empty
	}

	Vector4f(const Vector4f &v)
		:	x(v.x),
			y(v.y),
			z(v.z),
			w(v.w)
	{
		//	Empty
	}

	Vector4f(float vX, float vY, float vZ, float vW)
		:	x(vX),
			y(vY),
			z(vZ),
			w(vW)
	{
		//	Empty
	}

	Vector4f(const float * const xyzw)
		:	x(xyzw[0]),
			y(xyzw[1]),
			z(xyzw[2]),
			w(xyzw[3])
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
	inline void set(float x, float y, float z, float w)
	{
		v[0] = x;
		v[1] = y;
		v[2] = z;
		v[3] = w;
	}

	/*
		Set vector by array
	*/
	inline void set(const float * const xyzw)
	{
		x = xyzw[0];
		y = xyzw[1];
		z = xyzw[2];
		w = xyzw[3];
	}

	/*
		Update vector by vactor
	*/
	inline void set(const Vector4f &v)
	{
		x = v.x;
		y = v.y;
		z = v.z;
		w = v.w;
	}
	
	/*
		Update vector by value
	*/
	inline void update(float x, float y, float z)
	{
		v[0] += x;
		v[1] += y;
		v[2] += z;
		v[3] += w;
	}

	/*
		Update vector by array
	*/
	inline void update(const float * const xyzw)
	{
		x += xyzw[0];
		y += xyzw[1];
		z += xyzw[2];
		w += xyzw[3];
	}

	/*
		Update vector by vactor
	*/
	inline void update(const Vector4f &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
	}
	
	/*
		This function is called to set the vector to a null vector.
	*/
	inline void null()
	{
		x = 0.0f;
		y = 0.0f;
		z = 0.0f;
		w = 0.0f;
	}
	
	/*
		This function is called to check the vector is a null vector.
	*/
	inline bool isNull() const
	{
		return (x == 0 && y == 0 && z == 0 && w == 0);
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
			w /= r;
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
		return (x * x + y * y + z * z + w * w);
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

	inline const Vector4f& operator += (const Vector4f &v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;
		return *this;
	}

	inline const Vector4f& operator -= (const Vector4f &v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;
		return *this;
	}

	inline const Vector4f& operator *= (float v)
	{
		x *= v;
		y *= v;
		z *= v;
		w *= v;
		return *this;
	}

	inline const Vector4f& operator /= (float v)
	{
		x /= v;
		y /= v;
		z /= v;
		w /= v;
		return *this;
	}

	inline const Vector4f& operator = (float v)
	{
		x = v;
		y = v;
		z = v;
		w = v;
		return *this;
	}
	
	/*
		Operator for retrieving data
	*/

	inline const float& operator[](size_t i) const 
	{
		if (i > 4) i = 3;
		return v[i];
	}
	
	/*
		Operator for modifying data
	*/
	inline float& operator[](size_t i) 
	{
		if (i > 4) i = 3;
		return v[i];
	}
	
	/*
		Check equality to target vector
	*/
	inline bool operator == (const Vector4f &v) const
	{		
		return ((x == v.x) && (y == v.y) && (z == v.z) && (w == v.w));
	}
	
	/*
		Check inequality to target vector
	*/
	inline bool operator != (const Vector4f &v) const
	{		
		return !(*this == v);
	}
};
//--------------------------------------------------------------------

//	Global null vector
static Vector4f g_nullVector4f(0.0f, 0.0f, 0.0f, 0.0f);
//--------------------------------------------------------------------

/*
	Arithmetic operators.
*/

// operators +
inline Vector4f operator + (const Vector4f &v1, const Vector4f &v2)
{
	return Vector4f(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
}
//--------------------------------------------------------------------

// operators -
inline Vector4f operator - (const Vector4f &v1, const Vector4f &v2)
{
	return Vector4f(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
}
//--------------------------------------------------------------------

// operators *
inline Vector4f operator * (const Vector4f &v, const float &i)
{
	return Vector4f(v.x * i, v.y * i, v.z * i, v.w * i);
}
//--------------------------------------------------------------------

	inline Vector4f operator * (const float &i, const Vector4f &v)
{
	return Vector4f(i * v.x, i * v.y, i * v.z, i * v.w);
}
//--------------------------------------------------------------------

// operators /
inline Vector4f operator / (const Vector4f &v, const float &i)
{
	return Vector4f(v.x / i, v.y / i, v.z / i, v.w / i);
}
//--------------------------------------------------------------------
	
inline Vector4f operator / (const float &i, const Vector4f &v)
{
	return Vector4f(i / v.x, i / v.y, i / v.z, i / v.w);
}
//--------------------------------------------------------------------

/*
	Unary operators.
*/
inline Vector4f operator - (const Vector4f &v)
{
	return Vector4f(-v.x, -v.y, -v.z, -v.w);
}
//--------------------------------------------------------------------
	
inline Vector4f operator ++ (const Vector4f &v)
{
	return Vector4f(v.x + 1, v.y + 1, v.z + 1, v.w + 1);
}
//--------------------------------------------------------------------
	
inline Vector4f operator -- (const Vector4f &v)
{
	return Vector4f(v.x - 1, v.y - 1, v.z - 1, v.w - 1);
}
//--------------------------------------------------------------------

/*
	This function is called to get the length of vector in square format.
*/
inline float lengthSq(const Vector4f &v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the length of vector.
*/
inline float length(const Vector4f &v)
{
	return sqrt(lengthSq(v));
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the distance from target vector in square format.
*/
//	Change to non member function
inline float distanceSq(const Vector4f &v1, const Vector4f &v2)
{
	return lengthSq(v1 - v2);
}
//--------------------------------------------------------------------
	
/*
	This function is called to get the distance from target vector.
*/
inline float distance(const Vector4f &v1, const Vector4f &v2)
{
	return sqrt(distanceSq(v1, v2));
}
//--------------------------------------------------------------------

/*
	This function is called to normalize the target vector.
*/
inline Vector4f normalise(const Vector4f &v)
{
	float r = v.length();
	if (r != 0) 
		return Vector4f(v.x / r, v.y / r, v.z / r, v.w / r);

	return g_nullVector4f;
}
//--------------------------------------------------------------------

/*
	This function is called to calculate the dot product to a target vector.
*/

inline float dot(const Vector4f &v1, const Vector4f &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}
//--------------------------------------------------------------------

/*
	This function is called to calculate angle between vectors
*/

inline float getAngle(const Vector4f &v1, const Vector4f &v2) 
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