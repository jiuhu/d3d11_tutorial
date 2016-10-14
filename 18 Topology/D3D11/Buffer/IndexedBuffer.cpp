#include "IndexedBuffer.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

IndexedBuffer::IndexedBuffer()
	:	m_indexBuffer(nullptr),
		m_indexCount(0)
{
}
//--------------------------------------------------------------------

IndexedBuffer::~IndexedBuffer()
{
	safeRelease(m_indexBuffer);
}
//--------------------------------------------------------------------

bool IndexedBuffer::loadIndexedBuffer(const float * const vertices, UINT vertexCount, 
						const UINT * const indices, UINT indexCount,
						UINT attribute, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	if (!loadVertexBuffer(vertices, vertexCount, attribute, topology))
		return false;
	return loadIndexBuffer(indices, indexCount);
}
//--------------------------------------------------------------------

bool IndexedBuffer::loadIndexBuffer(const UINT * const indices, UINT indexCount)
{
	m_indexCount = indexCount;

	//----------------------------------------
	//	Set Index Data
	//----------------------------------------
    D3D11_SUBRESOURCE_DATA indexData;
	ZeroMemory(&indexData, sizeof(indexData));
    indexData.pSysMem = indices;
	
	//----------------------------------------
	//	Create Index Buffer
	//----------------------------------------
	D3D11_BUFFER_DESC ibd;
    ZeroMemory(&ibd, sizeof(ibd));
    ibd.Usage = D3D11_USAGE_DEFAULT;
    ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
    ibd.ByteWidth = sizeof(UINT) * m_indexCount;
	
    safeRelease(m_indexBuffer);
	HRESULT hr = Devices::get()->getDevice11()->CreateBuffer(&ibd, &indexData, &m_indexBuffer);
    if (FAILED(hr))
	{
		printErrorMessage(hr, "CreateIndexBuffer"); 
        return false;
	}

	return true;
}
//--------------------------------------------------------------------