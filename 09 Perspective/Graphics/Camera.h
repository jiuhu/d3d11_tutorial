#pragma once

#include "Utilities/Math/Matrix44f.h"
//--------------------------------------------------------------------

class WinInputDevice;
//--------------------------------------------------------------------

class Camera
{
public:

	struct CameraMatrix
	{
		//	View matrix.
		Matrix44f matView;

		//	Projection matrix.
		Matrix44f matProjection;
	};

	/*
		This function is called to define the perspective projection matrix.
	*/
	void perspectiveProjection(float width, float height, float nearPlane, float farPlane);

	/*
		This function is called to define the perspective projection matrix.
	*/
	void perspectiveProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane);

	/*
		This function is called to define the perspective projection matrix.
	*/
	void perspectiveProjectionFOV(float fov, float aspectRatio, float nearPlane, float farPlane);

	/*
		This function is called to define the orthographic projection matrix.
	*/
	void orthoProjection(float width, float height, float nearPlane, float farPlane);
	
	/*
		This function is called to define the orthographic projection matrix.
	*/
	void orthoProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane);
	
	/*
		This function is called to define the orthographic projection matrix.
	*/
	void orthoProjectionCenter(float width, float height, float nearPlane, float farPlane);

	/*
		This function is called to define the view matrix.
	*/
	void lookAt(const Vector3f &eye, const Vector3f &center, const Vector3f &up = Vector3f(0.0f, 1.0f, 0.0f));
	
	/*
		This function is called to define the view matrix.
	*/
	void lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ);
	
	/*
		This function is called to reset the camera view matrix.
	*/
	void reset();

	/*
		This function is called to move the camera.
	*/
	void slide(float x, float y, float z);

	/*
		This function is called to yaw camera (Left / Right)
	*/
	void yaw(float angle);

	/*
		This function is called to pitch camera (Up / Down)
	*/
	void pitch(float angle);

	/*
		This function is called to roll camera
	*/
	void roll(float angle);

	/*
		This function is called to update the input data to camera.
	*/
	void updateInput(WinInputDevice * const input);

	/*
		This function is called to retrieve the camera matrix.
	*/
	const CameraMatrix& getCameraMatrix() const;
	
private:

	//	Eye, Look and Up Vector.
	Vector3f _eye, _center, _up;

	//	The direction vectors.
	Vector3f _u, _v, _n;

	//	Camera matrices
	CameraMatrix m_matrices;

	/*
		This function is called to update the view matrix.
	*/
	void setViewMatrix();
};
//--------------------------------------------------------------------

inline void Camera::perspectiveProjectionFOV(float fov, float aspectRatio, float nearPlane, float farPlane)
{
	m_matrices.matProjection = matrixPerspectiveFOV(fov, aspectRatio, nearPlane, farPlane);
}
//--------------------------------------------------------------------

inline void Camera::perspectiveProjection(float width, float height, float nearPlane, float farPlane)
{
    m_matrices.matProjection = matrixPerspective(width, height, nearPlane, farPlane);
}
//--------------------------------------------------------------------

inline void Camera::perspectiveProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    m_matrices.matProjection = matrixPerspective(left, right, bottom, top, nearPlane, farPlane);
}
//--------------------------------------------------------------------

inline void Camera::orthoProjection(float width, float height, float nearPlane, float farPlane)
{
    m_matrices.matProjection = matrixOrtho(0.0f, width, height, 0.0f, nearPlane, farPlane);
}
//--------------------------------------------------------------------

inline void Camera::orthoProjection(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    m_matrices.matProjection = matrixOrtho(left, right, bottom, top, nearPlane, farPlane);
}
//--------------------------------------------------------------------

inline void Camera::orthoProjectionCenter(float width, float height, float nearPlane, float farPlane)
{
    m_matrices.matProjection = matrixOrtho(width, height, nearPlane, farPlane);
}
//--------------------------------------------------------------------

inline void Camera::lookAt(float eyeX, float eyeY, float eyeZ, float centerX, float centerY, float centerZ, float upX, float upY, float upZ)
{
	lookAt(Vector3f(eyeX, eyeY, eyeZ), Vector3f(centerX, centerY, centerZ), Vector3f(upX, upY, upZ));
}
//--------------------------------------------------------------------

inline void Camera::reset()
{
	m_matrices.matView = matrixLookAt(_eye, _center, _up);
}
//--------------------------------------------------------------------

inline const Camera::CameraMatrix& Camera::getCameraMatrix() const
{
	return m_matrices;
}
//--------------------------------------------------------------------

inline void Camera::setViewMatrix()
{
	m_matrices.matView = matrixView(_u, _v, _n, -_eye);
}
//--------------------------------------------------------------------