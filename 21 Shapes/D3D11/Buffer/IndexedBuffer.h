#pragma once

#include "VertexBuffer.h"
//--------------------------------------------------------------------

class IndexedBuffer : public VertexBuffer
{
public:

	/*
		Constructor.
	*/
	IndexedBuffer();

	/*
		Destructor.
	*/
	virtual ~IndexedBuffer();

	/*
		This function is called to load vertex buffer data from a float array.
	*/
	bool loadIndexedBuffer(const float * const vertices, UINT vertexCount, 
							const UINT * const indices, UINT indexCount,
							UINT attribute, D3D11_PRIMITIVE_TOPOLOGY topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		
	/*
		This function is called to load index buffer data.
	*/
	bool loadIndexBuffer(const UINT * const indices, UINT indexCount);
	
	/*
		This function is called to load buffer data from an obj file.
	*/
	bool loadIndexedBufferFromOBJFile(const char * const objFile, float scale = 1.0f, bool inverseTexture = true);

	/*
		This function is called to draw the buffer.
	*/
	void draw();

	/*
		This function is called to draw the indexed buffer.
	*/
	void drawIndexed();

protected:

	// Pointer to the index buffer.
	ID3D11Buffer * m_indexBuffer;

	// Index count.
	UINT m_indexCount;
};
//--------------------------------------------------------------------

inline void IndexedBuffer::drawIndexed() 
{
	if (m_deviceContext)
	{
		setVertexBuffer();
		m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
	}
}
//--------------------------------------------------------------------

inline void IndexedBuffer::draw() 
{
	if (m_indexBuffer)
		drawIndexed();
	else
		draw();
}
//--------------------------------------------------------------------