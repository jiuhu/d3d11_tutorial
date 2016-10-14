#pragma once

#include "D3D11/IRender.h"
//--------------------------------------------------------------------

class VertexBuffer : public IRender
{
public:

	/*
		Constructor.
	*/
	VertexBuffer();

	/*
		Destructor.
	*/
	~VertexBuffer();

	/*
		This function is called to load vertex buffer data from a float array.
	*/
	bool loadVertexBuffer(const float * const vertices, UINT vertexCount, bool hasNormal = false, bool hasTexture = false, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	/*
		This function is called to load vertex buffer data from a float array.
	*/
	bool loadVertexBuffer(const float * const vertices, UINT vertexCount, UINT attribute, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	/*
		This function is called to draw the buffer.
	*/
	virtual void draw();
	
	/*
		This function is called to draw the buffer with DrawAuto.
	*/
	void drawAuto();
	
protected:
	
	//	Pointer to the vertex buffer.
	ID3D11Buffer * m_vertexBuffer;

	//	Vertex count.
	UINT m_vertexCount;

	//	Stride.
	UINT m_stride;

	//	Primitive topology of the buffer.
	D3D11_PRIMITIVE_TOPOLOGY m_topology;
};
//--------------------------------------------------------------------

inline void VertexBuffer::draw() 
{
	if (m_deviceContext)
	{
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(m_topology);
		m_deviceContext->Draw(m_vertexCount, 0);
	}
}
//--------------------------------------------------------------------

inline void VertexBuffer::drawAuto() 
{
	if (m_deviceContext)
	{
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &offset);
		m_deviceContext->IASetPrimitiveTopology(m_topology);
		m_deviceContext->DrawAuto();
	}
}
//--------------------------------------------------------------------