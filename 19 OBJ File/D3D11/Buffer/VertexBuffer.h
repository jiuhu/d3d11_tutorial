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
	bool loadVertexBuffer(const float * const vertices, UINT vertexCount, bool hasNormal, bool hasTexture, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	/*
		This function is called to load vertex buffer data from a float array.
	*/
	bool loadColorVertexBuffer(const float * const vertices, UINT vertexCount, bool hasTexture = false, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST); 
	
	/*
		This function is called to load vertex buffer data from a float array.
	*/
	bool loadVertexBuffer(const float * const vertices, UINT vertexCount, UINT attribute, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	/*
		This function is called to load buffer data from an obj file.
	*/
	bool loadVertexBufferFromOBJFile(const char * const objFile, float scale = 1.0f, bool inverseTexture = true);

	/*
		This function is called to draw the vertex buffer.
	*/
	void draw();
	
	/*
		This function is called to draw the buffer with DrawAuto.
	*/
	void drawAuto();
	
	/*
		This function is called to draw the buffer with DrawAuto.
	*/
	void setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology);
	
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

inline void VertexBuffer::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY topology)
{
	m_topology = topology;
}
//--------------------------------------------------------------------