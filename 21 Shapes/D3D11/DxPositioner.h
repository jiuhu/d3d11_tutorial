#pragma once

#include "Graphics/Positioner.h"
#include "D3D11/Buffer/ConstantBuffer.h"
#include "Utilities/Math/Vector3f.h"
//--------------------------------------------------------------------

class DxPositioner : public Positioner
{
public:

	/*
		This function is called to initialize the world constant buffer.
	*/
	inline void init()
	{
		Positioner::init();
		m_worldCB.init(m_matrix);
		apply(1);
	}
	//--------------------------------------------------------------------

	/*
		This function is called to push a matrix.
	*/
	inline void apply(UINT startLocation = 1) const
	{
		m_worldCB.applyVS(startLocation);
	}
	//--------------------------------------------------------------------

	/*
		This function is called to pop a matrix.
	*/
	inline void pop()
	{
		Positioner::pop();
		m_worldCB.updateData(m_matrix);
	}
	//--------------------------------------------------------------------

	/*
		This function is called to update the matrix to constant buffer.
		Must called it after the transformation and before darwing.
	*/
	inline void update()
	{
		Positioner::update();
		m_worldCB.updateData(m_matrix);
	}
	//--------------------------------------------------------------------

	/*
		This function is called to reset transformation.
		Each transformation function must follow by a reset.
	*/
	inline void reset()
	{
		pop();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply a translation.
	*/
	inline void translation(float x, float y, float z = 0.0f)
	{
		push();
			m_matrix *= matrixTranslation(x, y, z);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply transformation through a 3D vector.
	*/
	inline void translation(const Vector3f &position)
	{	
		push();
			m_matrix *= matrixTranslation(position);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply a rotation about an arbitrary axis.
	*/
	inline void rotation(float angle, const Vector3f &axis)
	{
		push();
			m_matrix *= matrixRotationArbitrary(angle, axis);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply a rotation about an arbitrary axis.
	*/
	inline void rotation(float x, float y, float z)
	{
		push();
			m_matrix *= matrixFromEulerAngles(x, y, z);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply a rotation at x-axis.
	*/
	inline void rotationX(float angle)
	{
		push();
			m_matrix *= matrixRotationX(angle);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply a rotation at y-axis.
	*/
	inline void rotationY(float angle)
	{
		push();
			m_matrix *= matrixRotationY(angle);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply a rotation at z-axis.
	*/
	inline void rotationZ(float angle)
	{
		push();
			m_matrix *= matrixRotationZ(angle);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply transformation in 3D space.
	*/
	inline void transform(const Vector3f &position, float pitch, float yaw, float roll)
	{
		push();
			m_matrix *= matrixTranslation(position);
			m_matrix *= matrixFromEulerAngles(pitch, yaw, roll);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply transformation in 3D space.
	*/
	inline void transform(const Vector3f &position, const EulerAngles &angle)
	{
		push();
			m_matrix *= matrixTranslation(position);
			m_matrix *= matrixFromEulerAngles(angle);
			update();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply transformation.
	*/
	inline void transform(const Matrix44f &transformationMatrix)
	{
		push();
			m_matrix *= transformationMatrix;
			update();
	}
	//--------------------------------------------------------------------
	
private:
	
	//	The world constant buffer.
	ConstantBuffer m_worldCB;
};
//--------------------------------------------------------------------