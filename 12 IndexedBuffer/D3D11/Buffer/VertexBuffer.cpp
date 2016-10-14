#include "VertexBuffer.h"
#include "D3D11/DxDevices.h"
#include <fstream>
#include <string>
#include <vector>
#include "Utilities/Math/Vector2f.h"
#include "Utilities/Math/Vector3f.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

using namespace std;
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

bool VertexBuffer::loadOBJFile(const char * const objFile, float scale, bool inverseTexture) 
{
	ifstream fin(objFile);
	if(!fin)
	{
		outputMsg("Read file %s failed\n", objFile);
		return false;
	}

	vector<Vector3f> vertex;
	vector<Vector2f> texture;
	vector<Vector3f> normal;
	vector<unsigned int> vIndex;
	vector<unsigned int> tIndex;
	vector<unsigned int> nIndex;

	string attribute;

	// put them out to reduce some initiate time
	Vector3f v;
	Vector2f t;
	Vector3f n;
	unsigned int in[3];
	char divider;

	while(fin >> attribute)
	{
		// read the vertices
		if (attribute.compare("v") == 0)
		{
			fin >> v.x >> v.y >> v.z;
			v *= scale;
			vertex.push_back(v);
		}
		// read the textures coordinate
		else if(attribute.compare("vt") == 0)
		{
			fin >> t.x >> t.y; 
			if (inverseTexture) t.y = 1.0f - t.y;
			texture.push_back(t);
		}
		// read the normals
		else if (attribute.compare("vn") == 0)
		{
			fin >> n.x >> n.y >> n.z;
			normal.push_back(n);
		}
		// read the faces
		else if (attribute.compare("f") == 0)
		{
			fin >> in[0] >> divider >> in[1] >> divider >> in[2];
			vIndex.push_back(--in[0]);
			tIndex.push_back(--in[1]);
			nIndex.push_back(--in[2]);

			fin >> in[0] >> divider >> in[1] >> divider >> in[2];
			vIndex.push_back(--in[0]);
			tIndex.push_back(--in[1]);
			nIndex.push_back(--in[2]);

			fin >> in[0] >> divider >> in[1] >> divider >> in[2];
			vIndex.push_back(--in[0]);
			tIndex.push_back(--in[1]);
			nIndex.push_back(--in[2]);
		}
	}

	vector<float> vertexArray;
	
	UINT vertexCount = 0;
	for (UINT i = 0; i < vIndex.size(); i++) {
		vertexArray.push_back(vertex[vIndex[i]].x);
		vertexArray.push_back(vertex[vIndex[i]].y);
		vertexArray.push_back(vertex[vIndex[i]].z);

		vertexArray.push_back(normal[nIndex[i]].x);
		vertexArray.push_back(normal[nIndex[i]].y);
		vertexArray.push_back(normal[nIndex[i]].z);

		vertexArray.push_back(texture[tIndex[i]].x);
		vertexArray.push_back(texture[tIndex[i]].y);
	}

	loadVertexBuffer(&vertexArray[0], vIndex.size(), 8);

	return true;
}
//--------------------------------------------------------------------