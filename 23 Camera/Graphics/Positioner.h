#pragma once

#include "Utilities/Math/Matrix44f.h"
#include <stack>
//--------------------------------------------------------------------

class Positioner
{
public:

	/*
		This function is called to initialize the world constant buffer.
	*/
	inline void init()
	{
		identity();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to push a matrix.
	*/
	inline void push()
	{
		m_matrixStack.push(m_matrix);
		identity();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to pop a matrix.
	*/
	inline void pop()
	{
		if (!m_matrixStack.empty())
		{
			m_matrix = m_matrixStack.top();
			m_matrixStack.pop();
		}
	}
	//--------------------------------------------------------------------

	/*
		This function is called to update the matrix to constant buffer.
		Must called it after the transformation and before darwing.
	*/
	inline void update()
	{
		m_matrix *= m_matrixStack.top();
	}
	//--------------------------------------------------------------------

	/*
		This function is called to apply transformation.
	*/
	inline void setMatrix(const Matrix44f &matrix)
	{
		m_matrix = matrix;
	}
	//--------------------------------------------------------------------

	/*
		This function is called to set identity matrix.
	*/
	inline void identity()
	{
		m_matrix = matrixIdentity();
	}
	//--------------------------------------------------------------------
	
protected:

	//	The current matrix.
	Matrix44f m_matrix;

	//	The positioner matrix stack.
	std::stack<Matrix44f> m_matrixStack;
};
//--------------------------------------------------------------------