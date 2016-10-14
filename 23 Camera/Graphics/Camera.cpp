#include "Camera.h"
#include "Core/Input.h"
//--------------------------------------------------------------------

void Camera::lookAt(const Vector3f &eye, const Vector3f &center, const Vector3f &up)
{
	_eye = eye;
    _center = center;
    _up = up;

	//_n = _center - _eye;
	//_u = cross(_up, _n);
	//_n.normalise();
	//_u.normalise();
	//_v = cross(_n, _u);

	setViewMatrix();
}
//--------------------------------------------------------------------

void Camera::updateInput(WinInputDevice * const input)
{
	if (input->isKeyOnHold(VK_RBUTTON))
	{
		static int x, y;
		Input::get()->getRelativePosition(x, y);
		yawPitchRoll(toRadian((float)x), toRadian((float)-y), 0.0f);
	}
	//if (input->isKeyOnPress('A'))
	//{
	//	m_matrices.matView = matrixRotationY(toRadian(10.0f)) * m_matrices.matView;
	//}
	//if (input->isKeyOnPress('Z'))
	//{
	//	m_matrices.matView = matrixRotationZ(toRadian(10.0f)) * m_matrices.matView;
	//}
	
	if (input->isKeyOnPress('W'))
	{
		_center.y += 0.1f;
		setViewMatrix();
	}
	else if (input->isKeyOnPress('S'))
	{
		_center.y -= 0.1f;
		setViewMatrix();
	}

	if (input->isKeyOnPress('A'))
	{
		_center.x -= 0.1f;
		setViewMatrix();
	}
	else if (input->isKeyOnPress('D'))
	{
		_center.x += 0.1f;
		setViewMatrix();
	}

	if (input->isKeyOnPress('Q'))
	{
		_center.z -= 0.1f;
		setViewMatrix();
	}
	else if (input->isKeyOnPress('E'))
	{
		_center.z += 0.1f;
		setViewMatrix();
	}

	if (input->isKeyOnPress(VK_UP))
	{
		_eye.y += 0.1f;
		setViewMatrix();
	}
	else if (input->isKeyOnPress(VK_DOWN))
	{
		_eye.y -= 0.1f;
		setViewMatrix();
	}

	if (input->isKeyOnPress(VK_LEFT))
	{
		_eye.x -= 0.1f;
		setViewMatrix();
	}
	else if (input->isKeyOnPress(VK_RIGHT))
	{
		_eye.x += 0.1f;
		setViewMatrix();
	}

	if (input->isKeyOnPress(VK_PRIOR))
	{
		_eye.z -= 0.1f;
		setViewMatrix();
	}
	else if (input->isKeyOnPress(VK_NEXT))
	{
		_eye.z += 0.1f;
		setViewMatrix();
	}

	if (input->isKeyOnPress('R'))
	{
		reset();
	}

	float wheel = (float)input->getMouseWheel();
	if (wheel)
	{
		slide(0.0f, 0.0f, -wheel);
	}
}
//--------------------------------------------------------------------

void Camera::slide(float x, float y, float z)
{
	m_matrices.matView *= matrixTranslation(x, y, z);
	//_eye.x += x * _u.x + y * _v.x + z * _n.x;
	//_eye.y += x * _u.y + y * _v.y + z * _n.y;
	//_eye.z += x * _u.z + y * _v.z + z * _n.z;

	//_center.x += x * _u.x + y * _v.x + z * _n.x;
	//_center.y += x * _u.y + y * _v.y + z * _n.y;
	//_center.z += x * _u.z + y * _v.z + z * _n.z;
	//
	//setViewMatrix();
}
//--------------------------------------------------------------------

void Camera::yaw(float angle)
{
	m_matrices.matView = matrixRotationY(toRadian(angle)) * m_matrices.matView;
}
//--------------------------------------------------------------------

void Camera::pitch(float angle)
{
	m_matrices.matView = matrixRotationX(toRadian(angle)) * m_matrices.matView;
}
//--------------------------------------------------------------------

void Camera::roll(float angle)
{
	//float cs = cos(toRadian(angle));
	//float sn = sin(toRadian(angle));
	//Vector3f t(_u);
	//_u.set(cs * t.x - sn * _v.x, cs * t.y - sn * _v.y, cs * t.z - sn * _v.z);
	//_v.set(sn * t.x - cs * _v.x, sn * t.y - cs * _v.y, sn * t.z - cs * _v.z);
	//
	//setViewMatrix();
	
	m_matrices.matView = matrixRotationZ(toRadian(angle)) * m_matrices.matView;
}
//--------------------------------------------------------------------

void Camera::yawPitchRoll(float yaw, float pitch, float roll)
{
	m_matrices.matView = matrixFromEulerAngles(pitch, yaw, roll) * m_matrices.matView;
}
//--------------------------------------------------------------------