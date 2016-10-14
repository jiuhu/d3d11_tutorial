#pragma once

#include "Vector3f.h"
#include "MyMath.h"
#include <cstring>
//--------------------------------------------------------------------

/*
	Sora specifies matrix as follows,

			m11	m12	m13	m14			m0	m4	m8	m12
	M = 	m21	m22	m23	m24		=	m1	m5	m9	m13
			m31	m32	m33	m34			m2	m6	m10	m14
			m41	m42	m43	m44			m3	m7	m11	m15
*/

class Matrix44f
{
public:

	//	matrix elements.
	union
	{
		struct
		{
			float	m11, m21, m31, m41,
					m12, m22, m32, m42,
					m13, m23, m33, m43,
					m14, m24, m34, m44;
		};

		float m[16];
	};

	/*
		Constructors.
	*/
	Matrix44f()
	{
		//	Empty
	}

	Matrix44f(const float * const matrix)
	{
		memcpy(m, matrix, 16 * sizeof(float));
	}

	Matrix44f(float a1, float a2, float a3, float a4,
					float a5, float a6, float a7, float a8,
					float a9, float a10, float a11, float a12,
					float a13, float a14, float a15, float a16)
					:	m11(a1), m21(a2), m31(a3), m41(a4),
						m12(a5), m22(a6), m32(a7), m42(a8),
						m13(a9), m23(a10), m33(a11), m43(a12),
						m14(a13), m24(a14), m34(a15), m44(a16)
	{
		//	Empty
	}
		
	/*
		This function is called to set the matrix to a null matrix.
	*/
	inline void null()
	{
		m11 = 0.0f;	m21 = 0.0f;	m31 = 0.0f;	m41 = 0.0f;
		m12 = 0.0f;	m22 = 0.0f;	m32 = 0.0f;	m42 = 0.0f;
		m13 = 0.0f;	m23 = 0.0f;	m33 = 0.0f;	m43 = 0.0f;
		m14 = 0.0f;	m24 = 0.0f;	m34 = 0.0f;	m44 = 0.0f;
	}
		
	/*
		This function is called to set the matrix to an identity matrix.
	*/
	inline void identity()
	{
		m11 = 1.0f;	m21 = 0.0f;	m31 = 0.0f;	m41 = 0.0f;
		m12 = 0.0f;	m22 = 1.0f;	m32 = 0.0f;	m42 = 0.0f;
		m13 = 0.0f;	m23 = 0.0f;	m33 = 1.0f;	m43 = 0.0f;
		m14 = 0.0f;	m24 = 0.0f;	m34 = 0.0f;	m44 = 1.0f;
	}
		
	/*
		This function is called to check the matrix is a null matrix.
	*/
	inline bool isNull() const
	{
		return (m11 == 0.0f && m21 == 0.0f && m31 == 0.0f && m41 == 0.0f && 
				m12 == 0.0f && m22 == 0.0f && m32 == 0.0f && m42 == 0.0f && 
				m13 == 0.0f && m23 == 0.0f && m33 == 0.0f && m43 == 0.0f && 
				m14 == 0.0f && m24 == 0.0f && m34 == 0.0f && m44 == 0.0f);
	}

	/*
		This function is called to set values to the matrix.
	*/
	inline void set(float a1, float a2, float a3, float a4,
					float a5, float a6, float a7, float a8,
					float a9, float a10, float a11, float a12,
					float a13, float a14, float a15, float a16)
	{
		m11 = a1;	m21 = a2;	m31 = a3;	m41 = a4;
		m12 = a5;	m22 = a6;	m32 = a7;	m42 = a8;
		m13 = a9;	m23 = a10;	m33 = a11;	m43 = a12;
		m14 = a13;	m24 = a14;	m34 = a15;	m44 = a16;
	}
				
	/*
		This function is called to an array to the matrix.
	*/
	inline void set(const float * const matrix)
	{
		memcpy(m, matrix, 16 * sizeof(float));
	}

	/*
		This function is called to multiply the matrix with a scalar.
	*/
	void scalar(float k)
	{
		m11 *= k;	m21 *= k;	m31 *= k;	m41 *= k;
		m12 *= k;	m22 *= k;	m32 *= k;	m42 *= k;
		m13 *= k;	m23 *= k;	m33 *= k;	m43 *= k;
		m14 *= k;	m24 *= k;	m34 *= k;	m44 *= k;
	}

	/*
		This function is called to calculate the determinant of the matrix.
	*/
	float determinant() const
	{
		return	
			(m11 * m22 - m12 * m21) * (m33 * m44 - m34 * m43)
			-(m11 * m23 - m13 * m21) * (m32 * m44 - m34 * m42)
			+(m11 * m24 - m14 * m21) * (m32 * m43 - m33 * m42)
			+(m12 * m23 - m13 * m22) * (m31 * m44 - m34 * m41)
			-(m12 * m24 - m14 * m22) * (m31 * m43 - m33 * m41)
			+(m13 * m24 - m14 * m23) * (m31 * m42 - m32 * m41);
	}

	/*
		This function is called to invert the matrix.
	*/
	inline void inverse()
	{
		float det = determinant();
		if (det * det < EPSILON)
		{
			return;
		}
		float s = 1 / det;
		set(
			s*(m22*(m33*m44 - m34*m43) + m23*(m34*m42 - m32*m44) + m24*(m32*m43 - m33*m42)),
			s*(m32*(m13*m44 - m14*m43) + m33*(m14*m42 - m12*m44) + m34*(m12*m43 - m13*m42)),
			s*(m42*(m13*m24 - m14*m23) + m43*(m14*m22 - m12*m24) + m44*(m12*m23 - m13*m22)),
			s*(m12*(m24*m33 - m23*m34) + m13*(m22*m34 - m24*m32) + m14*(m23*m32 - m22*m33)),
			s*(m23*(m31*m44 - m34*m41) + m24*(m33*m41 - m31*m43) + m21*(m34*m43 - m33*m44)),
			s*(m33*(m11*m44 - m14*m41) + m34*(m13*m41 - m11*m43) + m31*(m14*m43 - m13*m44)),
			s*(m43*(m11*m24 - m14*m21) + m44*(m13*m21 - m11*m23) + m41*(m14*m23 - m13*m24)),
			s*(m13*(m24*m31 - m21*m34) + m14*(m21*m33 - m23*m31) + m11*(m23*m34 - m24*m33)),
			s*(m24*(m31*m42 - m32*m41) + m21*(m32*m44 - m34*m42) + m22*(m34*m41 - m31*m44)),
			s*(m34*(m11*m42 - m12*m41) + m31*(m12*m44 - m14*m42) + m32*(m14*m41 - m11*m44)),
			s*(m44*(m11*m22 - m12*m21) + m41*(m12*m24 - m14*m22) + m42*(m14*m21 - m11*m24)),
			s*(m14*(m22*m31 - m21*m32) + m11*(m24*m32 - m22*m34) + m12*(m21*m34 - m24*m31)),
			s*(m21*(m33*m42 - m32*m43) + m22*(m31*m43 - m33*m41) + m23*(m32*m41 - m31*m42)),
			s*(m31*(m13*m42 - m12*m43) + m32*(m11*m43 - m13*m41) + m33*(m12*m41 - m11*m42)),
			s*(m41*(m13*m22 - m12*m23) + m42*(m11*m23 - m13*m21) + m43*(m12*m21 - m11*m22)),
			s*(m11*(m22*m33 - m23*m32) + m12*(m23*m31 - m21*m33) + m13*(m21*m32 - m22*m31))
		);
	}

	//	Assignment operator.

	//inline const Matrix44f& operator = (const Matrix44f &m)
	//{
	//	m11 = m.m11;	m21 = m.m21;	m31 = m.m31;	m41 = m.m41;
	//	m12 = m.m12;	m22 = m.m22;	m32 = m.m32;	m42 = m.m42;
	//	m13 = m.m13;	m23 = m.m23;	m33 = m.m33;	m43 = m.m43;
	//	m14 = m.m14;	m24 = m.m24;	m34 = m.m34;	m44 = m.m44;
	//	return *this;
	//}
	
	/*
		Operator for retrieving data
	*/

	inline const float& operator[](size_t i) const 
	{
		if (i > 16) i = 15;
		return m[i];
	}
	
	/*
		Operator for modifying data
	*/
	inline float& operator[](size_t i) 
	{
		if (i > 16) i = 15;
		return m[i];
	}

	//inline const Matrix44f& operator = (const Matrix44f &m)
	//{
	//	m11 = m.m11;	m21 = m.m21;	m31 = m.m31;	m41 = m.m41;
	//	m12 = m.m12;	m22 = m.m22;	m32 = m.m32;	m42 = m.m42;
	//	m13 = m.m13;	m23 = m.m23;	m33 = m.m33;	m43 = m.m43;
	//	m14 = m.m14;	m24 = m.m24;	m34 = m.m34;	m44 = m.m44;
	//	return *this;
	//}
	
	/*
		Check equality to target vector
	*/
	inline bool operator == (const Matrix44f &mat) const
	{		
		return (memcmp(m, mat.m, sizeof(float) * 16) == 0);
	}
	
	/*
		Check inequality to target vector
	*/
	inline bool operator != (const Matrix44f &m) const
	{		
		return !(*this == m);
	}

	

	inline const Matrix44f& operator *= (const Matrix44f &mat)
	{
		set(	m11 * mat.m11 + m12 * mat.m21 + m13 * mat.m31 + m14 * mat.m41,
				m21 * mat.m11 + m22 * mat.m21 + m23 * mat.m31 + m24 * mat.m41,
				m31 * mat.m11 + m32 * mat.m21 + m33 * mat.m31 + m34 * mat.m41,
				m41 * mat.m11 + m42 * mat.m21 + m43 * mat.m31 + m44 * mat.m41,
				m11 * mat.m12 + m12 * mat.m22 + m13 * mat.m32 + m14 * mat.m42,
				m21 * mat.m12 + m22 * mat.m22 + m23 * mat.m32 + m24 * mat.m42,
				m31 * mat.m12 + m32 * mat.m22 + m33 * mat.m32 + m34 * mat.m42,
				m41 * mat.m12 + m42 * mat.m22 + m43 * mat.m32 + m44 * mat.m42,
				m11 * mat.m13 + m12 * mat.m23 + m13 * mat.m33 + m14 * mat.m43,
				m21 * mat.m13 + m22 * mat.m23 + m23 * mat.m33 + m24 * mat.m43,
				m31 * mat.m13 + m32 * mat.m23 + m33 * mat.m33 + m34 * mat.m43,
				m41 * mat.m13 + m42 * mat.m23 + m43 * mat.m33 + m44 * mat.m43,
				m11 * mat.m14 + m12 * mat.m24 + m13 * mat.m34 + m14 * mat.m44,
				m21 * mat.m14 + m22 * mat.m24 + m23 * mat.m34 + m24 * mat.m44,
				m31 * mat.m14 + m32 * mat.m24 + m33 * mat.m34 + m34 * mat.m44,
				m41 * mat.m14 + m42 * mat.m24 + m43 * mat.m34 + m44 * mat.m44
		);
		return *this;
	}
};
//--------------------------------------------------------------------

//	Global null matrix
static Matrix44f g_nullMatrix44f(0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f,
								0.0f, 0.0f, 0.0f, 0.0f);
//--------------------------------------------------------------------

/*
	This function is called to set the given matrix to an identity matrix.
*/
inline void matrixIdentity(Matrix44f &m)
{
	m.m11 = 1.0f;	m.m21 = 0.0f;	m.m31 = 0.0f;	m.m41 = 0.0f;
	m.m12 = 0.0f;	m.m22 = 1.0f;	m.m32 = 0.0f;	m.m42 = 0.0f;
	m.m13 = 0.0f;	m.m23 = 0.0f;	m.m33 = 1.0f;	m.m43 = 0.0f;
	m.m14 = 0.0f;	m.m24 = 0.0f;	m.m34 = 0.0f;	m.m44 = 1.0f;
}
//--------------------------------------------------------------------

/*
	This function is called to create an identity matrix.
*/
inline Matrix44f matrixIdentity()
{
	return Matrix44f(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to a rotation matrix about the x-axis.
*/
inline Matrix44f matrixTranslation(float x, float y, float z)
{
	return Matrix44f(1.0f, 0.0f, 0.0f, x,
					0.0f, 1.0f, 0.0f, y,
					0.0f, 0.0f, 1.0f, z,
					0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to a rotation matrix about the x-axis.
*/
inline Matrix44f matrixTranslation(const Vector3f v)
{
	return Matrix44f(1.0f, 0.0f, 0.0f, v.x,
					0.0f, 1.0f, 0.0f, v.y,
					0.0f, 0.0f, 1.0f, v.z,
					0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to a rotation matrix about the x-axis.
*/
inline Matrix44f matrixRotationX(float theta)
{
	return Matrix44f(1.0f, 0.0f, 0.0f, 0.0f,
					0.0f, cos(theta), sin(theta), 0.0f,
					0.0f, -sin(theta), cos(theta), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to a rotation matrix about the y-axis.
*/
inline Matrix44f matrixRotationY(float theta)
{
	return Matrix44f(cos(theta), 0.0f, -sin(theta), 0.0f,
					0.0f, 1.0f, 0.0f, 0.0f,
					sin(theta), 0.0f, cos(theta), 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to a rotation matrix about the z-axis.
*/
inline Matrix44f matrixRotationZ(float theta)
{
	return Matrix44f(cos(theta), sin(theta), 0.0f, 0.0f,
					-sin(theta), cos(theta), 0.0f, 0.0f,
					0.0f, 0.0f, 1.0f, 0.0f,
					0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to create a tranpose of the given matrix.
*/
inline Matrix44f matrixTranspose(const Matrix44f &m)
{
	return Matrix44f(	m.m11, m.m12, m.m13, m.m14,
						m.m21, m.m22, m.m23, m.m24,
						m.m31, m.m32, m.m33, m.m34,
						m.m41, m.m42, m.m43, m.m44);
}
//--------------------------------------------------------------------

/*
	This function is called to create set view matrix.
*/
inline Matrix44f matrixView(const Vector3f &u, const Vector3f &v, const Vector3f &n, const Vector3f &eye)
{
	return Matrix44f(	u.x, u.y, u.z, dot(eye, u),
						v.x, v.y, v.z, dot(eye, v),
						n.x, n.y, n.z, dot(eye, n),
						0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to create set matrix LookAt.
*/
inline Matrix44f matrixLookAt(const Vector3f &eye, const Vector3f &look, const Vector3f &up)
{
	Vector3f n = eye - look;
	Vector3f u = cross(up, n);
	n.normalise();
	u.normalise();
	Vector3f v = cross(n, u);
	Vector3f d(dot(eye, u), dot(eye, v), dot(eye, n));

	return matrixView(u, v, n, eye);
}
//--------------------------------------------------------------------

/*
	This function is called to set orthographic projection matrix.
	Centered at origin.
*/
inline Matrix44f matrixOrtho(float width, float height, float N, float F)
{
	return Matrix44f(	2.0f / width, 0.0f, 0.0f, 0.0f,
						0.0f, 2.0f / height, 0.0f, 0.0f,
						0.0f, 0.0f, 1.0f / (F - N), N / (N - F),
						0.0f, 0.0f, 1.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to set orthographic projection matrix.
*/
inline Matrix44f matrixOrtho(float left, float right, float bottom, float top, float N, float F)
{
	return Matrix44f(	2.0f / (right - left), 0.0f, 0.0f, (left + right) / (left - right),
						0.0f, 2.0f / (top - bottom), 0.0f, (top + bottom) / (bottom - top),
						0.0f, 0.0f, 1.0f / (F - N), N / (N - F),
						0.0f, 0.0f, 0.0f, 1.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to set perspective projection matrix.
*/
inline Matrix44f matrixPerspectiveFOV(float viewAngle, float aspect, float N, float F)
{
	float theta = toRadian(viewAngle / 2.0f);
	float cot = 1.0f / tan(theta);
	float NminF = N - F;

	return Matrix44f(	cot / aspect, 0.0f, 0.0f, 0.0f,
						0.0f, cot, 0.0f, 0.0f,
						0.0f, 0.0f, F / (F - N), (N * F) / (N - F),
						0.0f, 0.0f, 1.0f, 0.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to set perspective projection matrix.
*/
inline Matrix44f matrixPerspective(float width, float height, float N, float F)
{
	float twoN = N * 2;
	return Matrix44f(	twoN / width, 0.0f, 0.0f, 0.0f,
						0.0f, twoN / height, 0.0f, 0.0f,
						0.0f, 0.0f, F / (F - N), (N * F) / (N - F),
						0.0f, 0.0f, 1.0f, 0.0f);
}
//--------------------------------------------------------------------

/*
	This function is called to set perspective matrix.
*/	
inline Matrix44f matrixPerspective(float left, float right, float bottom, float top, float N, float F)
{
	//float theta = toRadian(viewAngle / 2.0f);
	//float top = N * tan(theta);
	//float bottom = -top;
	//float right = top * aspect;
	//float left = -right;

//2*zn/(r-l)   0            0              0
//0            2*zn/(t-b)   0              0
//(l+r)/(l-r)  (t+b)/(b-t)  zf/(zf-zn)     1
//0            0            zn*zf/(zn-zf)  0

	float twoN = N * 2;
	return Matrix44f(	twoN / (right - left), 0.0f, (right + left) / (left - right), 0.0f,
						0.0f, twoN / (top - bottom), (top + bottom) / (bottom - top), 0.0f, 
						0.0f, 0.0f, F / (F - N), (N * F) / (N - F),
						0.0f, 0.0f, 1.0f, 0.0f);
}
//--------------------------------------------------------------------

// operators *

inline Matrix44f operator * (float k, const Matrix44f &m)
{
	return Matrix44f(	k * m.m11, k * m.m21, k * m.m31, k * m.m41,
						k * m.m12, k * m.m22, k * m.m32, k * m.m42,
						k * m.m13, k * m.m23, k * m.m33, k * m.m43,
						k * m.m14, k * m.m24, k * m.m34, k * m.m44);
}
//--------------------------------------------------------------------
		
/*
	For matC = m1 * m2;

		m2
	m1	matC
*/
inline Matrix44f operator * (const Matrix44f &m1, const Matrix44f &m2)
{
	return Matrix44f(	m1.m11 * m2.m11 + m1.m12 * m2.m21 + m1.m13 * m2.m31 + m1.m14 * m2.m41,
						m1.m21 * m2.m11 + m1.m22 * m2.m21 + m1.m23 * m2.m31 + m1.m24 * m2.m41,
						m1.m31 * m2.m11 + m1.m32 * m2.m21 + m1.m33 * m2.m31 + m1.m34 * m2.m41,
						m1.m41 * m2.m11 + m1.m42 * m2.m21 + m1.m43 * m2.m31 + m1.m44 * m2.m41,
						m1.m11 * m2.m12 + m1.m12 * m2.m22 + m1.m13 * m2.m32 + m1.m14 * m2.m42,
						m1.m21 * m2.m12 + m1.m22 * m2.m22 + m1.m23 * m2.m32 + m1.m24 * m2.m42,
						m1.m31 * m2.m12 + m1.m32 * m2.m22 + m1.m33 * m2.m32 + m1.m34 * m2.m42,
						m1.m41 * m2.m12 + m1.m42 * m2.m22 + m1.m43 * m2.m32 + m1.m44 * m2.m42,
						m1.m11 * m2.m13 + m1.m12 * m2.m23 + m1.m13 * m2.m33 + m1.m14 * m2.m43,
						m1.m21 * m2.m13 + m1.m22 * m2.m23 + m1.m23 * m2.m33 + m1.m24 * m2.m43,
						m1.m31 * m2.m13 + m1.m32 * m2.m23 + m1.m33 * m2.m33 + m1.m34 * m2.m43,
						m1.m41 * m2.m13 + m1.m42 * m2.m23 + m1.m43 * m2.m33 + m1.m44 * m2.m43,
						m1.m11 * m2.m14 + m1.m12 * m2.m24 + m1.m13 * m2.m34 + m1.m14 * m2.m44,
						m1.m21 * m2.m14 + m1.m22 * m2.m24 + m1.m23 * m2.m34 + m1.m24 * m2.m44,
						m1.m31 * m2.m14 + m1.m32 * m2.m24 + m1.m33 * m2.m34 + m1.m34 * m2.m44,
						m1.m41 * m2.m14 + m1.m42 * m2.m24 + m1.m43 * m2.m34 + m1.m44 * m2.m44
		);
}
//--------------------------------------------------------------------

/*
	For matC = m * v
*/
inline Vector3f operator * (const Matrix44f &m, const Vector3f &v)
{
	return Vector3f(m.m11 * v.x + m.m12 * v.y + m.m13 * v.z,
					m.m21 * v.x + m.m22 * v.y + m.m23 * v.z,
					m.m31 * v.x + m.m32 * v.y + m.m33 * v.z);
}

/*
	This function is called to find the inverse of target matrix.
*/
inline Matrix44f inverse(const Matrix44f &m)
{
	float det = m.determinant();
	if (det * det < EPSILON)
	{
		return g_nullMatrix44f;
	}
	float s = 1 / det;
	return Matrix44f(
		s*(m.m22*(m.m33*m.m44 - m.m34*m.m43) + m.m23*(m.m34*m.m42 - m.m32*m.m44) + m.m24*(m.m32*m.m43 - m.m33*m.m42)),
		s*(m.m32*(m.m13*m.m44 - m.m14*m.m43) + m.m33*(m.m14*m.m42 - m.m12*m.m44) + m.m34*(m.m12*m.m43 - m.m13*m.m42)),
		s*(m.m42*(m.m13*m.m24 - m.m14*m.m23) + m.m43*(m.m14*m.m22 - m.m12*m.m24) + m.m44*(m.m12*m.m23 - m.m13*m.m22)),
		s*(m.m12*(m.m24*m.m33 - m.m23*m.m34) + m.m13*(m.m22*m.m34 - m.m24*m.m32) + m.m14*(m.m23*m.m32 - m.m22*m.m33)),
		s*(m.m23*(m.m31*m.m44 - m.m34*m.m41) + m.m24*(m.m33*m.m41 - m.m31*m.m43) + m.m21*(m.m34*m.m43 - m.m33*m.m44)),
		s*(m.m33*(m.m11*m.m44 - m.m14*m.m41) + m.m34*(m.m13*m.m41 - m.m11*m.m43) + m.m31*(m.m14*m.m43 - m.m13*m.m44)),
		s*(m.m43*(m.m11*m.m24 - m.m14*m.m21) + m.m44*(m.m13*m.m21 - m.m11*m.m23) + m.m41*(m.m14*m.m23 - m.m13*m.m24)),
		s*(m.m13*(m.m24*m.m31 - m.m21*m.m34) + m.m14*(m.m21*m.m33 - m.m23*m.m31) + m.m11*(m.m23*m.m34 - m.m24*m.m33)),
		s*(m.m24*(m.m31*m.m42 - m.m32*m.m41) + m.m21*(m.m32*m.m44 - m.m34*m.m42) + m.m22*(m.m34*m.m41 - m.m31*m.m44)),
		s*(m.m34*(m.m11*m.m42 - m.m12*m.m41) + m.m31*(m.m12*m.m44 - m.m14*m.m42) + m.m32*(m.m14*m.m41 - m.m11*m.m44)),
		s*(m.m44*(m.m11*m.m22 - m.m12*m.m21) + m.m41*(m.m12*m.m24 - m.m14*m.m22) + m.m42*(m.m14*m.m21 - m.m11*m.m24)),
		s*(m.m14*(m.m22*m.m31 - m.m21*m.m32) + m.m11*(m.m24*m.m32 - m.m22*m.m34) + m.m12*(m.m21*m.m34 - m.m24*m.m31)),
		s*(m.m21*(m.m33*m.m42 - m.m32*m.m43) + m.m22*(m.m31*m.m43 - m.m33*m.m41) + m.m23*(m.m32*m.m41 - m.m31*m.m42)),
		s*(m.m31*(m.m13*m.m42 - m.m12*m.m43) + m.m32*(m.m11*m.m43 - m.m13*m.m41) + m.m33*(m.m12*m.m41 - m.m11*m.m42)),
		s*(m.m41*(m.m13*m.m22 - m.m12*m.m23) + m.m42*(m.m11*m.m23 - m.m13*m.m21) + m.m43*(m.m12*m.m21 - m.m11*m.m22)),
		s*(m.m11*(m.m22*m.m33 - m.m23*m.m32) + m.m12*(m.m23*m.m31 - m.m21*m.m33) + m.m13*(m.m21*m.m32 - m.m22*m.m31))
	);
}
//--------------------------------------------------------------------

inline Vector3f getMatrixTranslation(const Matrix44f &mat)
{
	return Vector3f(mat.m41, mat.m42, mat.m43);
}
//--------------------------------------------------------------------