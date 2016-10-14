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
		This function is called to draw the buffer.
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
		UINT offset = 0;
		m_deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &m_stride, &offset);
		m_deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
		m_deviceContext->IASetPrimitiveTopology(m_topology);
		m_deviceContext->DrawIndexed(m_indexCount, 0, 0);
	}
}
//--------------------------------------------------------------------