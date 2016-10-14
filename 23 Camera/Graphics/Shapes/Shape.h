#pragma once

#include "D3D11/Buffer/VertexBuffer.h"
//--------------------------------------------------------------------

class Shape
{
public:

	/*
		This function is called to initialize the shape object with an available buffer.
	*/
	bool setVertexBuffer(VertexBuffer &shape)
	{	
		m_shapeBuffer = shape;
		return true;
	}

	/*
		This function is called to set a shape based on the given vertices.
	*/
	bool setVertexBuffer(const float * const vertices, UINT vertexCount, bool hasNormal, bool hasTexture)
	{	
		return m_shapeBuffer.loadVertexBuffer(vertices, vertexCount, hasNormal, hasTexture);
	}

	/*
		This function is called to set a vertex only shape.
	*/
	bool setVertexBuffer(const float * const vertices, unsigned int vertexCount, UINT attribute = 3)
	{	
		return m_shapeBuffer.loadVertexBuffer(vertices, vertexCount, attribute);
	}

	/*
		This function is called to draw the shape.
	*/
	void draw() const
	{
		m_shapeBuffer.draw();
	}
		
protected:

	//	Pointer to the geometry vertex buffer.
	VertexBuffer m_shapeBuffer;
};
//--------------------------------------------------------------------