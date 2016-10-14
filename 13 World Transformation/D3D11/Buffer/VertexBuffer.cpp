#include "VertexBuffer.h"
#include "D3D11/DxDevices.h"
//--------------------------------------------------------------------

VertexBuffer::VertexBuffer()
	:	m_vertexBuffer(nullptr),
		m_vertexCount(3),
		m_stride(3),
		m_topology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
{
    //	Empty
}
//--------------------------------------------------------------------

VertexBuffer::~VertexBuffer()
{
	safeRelease(m_vertexBuffer);
}
//--------------------------------------------------------------------

bool VertexBuffer::loadVertexBuffer(const float * const vertices, UINT vertexCount, bool hasNormal, bool hasTexture, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	//----------------------------------------
	//	Calculate vertex attributes
	//----------------------------------------
	int vertexAttributesCount = 3;
	if (hasNormal) vertexAttributesCount += 3;
	if (hasTexture) vertexAttributesCount += 2;
	
	return loadVertexBuffer(vertices, vertexCount, vertexAttributesCount, topology);
}
//--------------------------------------------------------------------

bool VertexBuffer::loadColorVertexBuffer(const float * const vertices, UINT vertexCount, bool hasTexture, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	//----------------------------------------
	//	Calculate vertex attributes
	//----------------------------------------
	int vertexAttributesCount = 3 + 4;
	if (hasTexture) vertexAttributesCount += 2;
	
	return loadVertexBuffer(vertices, vertexCount, vertexAttributesCount, topology);
}
//--------------------------------------------------------------------

bool VertexBuffer::loadVertexBuffer(const float * const vertices, UINT vertexCount, UINT attribute, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	//----------------------------------------
	//	Set Vertex Data
	//----------------------------------------
    D3D11_SUBRESOURCE_DATA vertexData;
	ZeroMemory(&vertexData, sizeof(vertexData));
    vertexData.pSysMem = vertices;
	
	//----------------------------------------
	//	Create Vertex Buffer
	//----------------------------------------
    D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = sizeof(float) * vertexCount * attribute;
    
	safeRelease(m_vertexBuffer);
	HRESULT hr = Devices::get()->getDevice11()->CreateBuffer(&bd, &vertexData, &m_vertexBuffer);
    if (FAILED(hr))
	{
		printErrorMessage(hr, "CreateBuffer"); 
        return false;
	}
	
	//----------------------------------------
	//	Set for the rest
	//----------------------------------------
	m_vertexCount = vertexCount;
    
    m_stride = sizeof(float) * attribute;

	m_topology = topology;

	return true;
}
//--------------------------------------------------------------------