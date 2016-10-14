#include "IndexedBuffer.h"
#include "D3D11/DxDevices.h"
#include <fstream>
#include <string>
#include <vector>
#include "Utilities/Debug.h"
#include "Utilities/Math/Vector2f.h"
#include "Utilities/Math/Vector3f.h"
//--------------------------------------------------------------------

using namespace std;
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

bool IndexedBuffer::loadOBJFile(const char * const objFile, float scale) 
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

	m_indexCount = vIndex.size();

	vector<float> vertexArray;
	vector<unsigned int> indexArray;
	
	UINT vertexCount = 0;
	for (UINT i = 0; i < m_indexCount; i++) {
		indexArray.push_back(i);

		vertexArray.push_back(vertex[vIndex[i]].x);
		vertexArray.push_back(vertex[vIndex[i]].y);
		vertexArray.push_back(vertex[vIndex[i]].z);

		vertexArray.push_back(normal[nIndex[i]].x);
		vertexArray.push_back(normal[nIndex[i]].y);
		vertexArray.push_back(normal[nIndex[i]].z);

		vertexArray.push_back(1.0f - texture[tIndex[i]].x);
		vertexArray.push_back(1.0f - texture[tIndex[i]].y);
	}

	loadVertexBuffer(&vertexArray[0], m_indexCount, true, true);

	loadIndexBuffer(&indexArray[0]);

	return true;
}
//--------------------------------------------------------------------


bool IndexedBuffer::loadIndexedBuffer(const float * const vertices, UINT vertexCount, 
						const unsigned int * const indices, UINT indexCount,
						UINT attribute, D3D11_PRIMITIVE_TOPOLOGY topology)
{
	if (!loadVertexBuffer(vertices, vertexCount, attribute, topology))
		return false;
	m_indexCount = indexCount;
	return loadIndexBuffer(indices);
}
//--------------------------------------------------------------------

bool IndexedBuffer::loadIndexBuffer(const unsigned int * const indices)
{
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
    ibd.ByteWidth = sizeof(unsigned int) * m_indexCount;
	
    safeRelease(m_indexBuffer);
	HRESULT hr = Devices::get()->getDevice11()->CreateBuffer(&ibd, &indexData, &m_indexBuffer);
    if (FAILED(hr))
	{
		printErrorMessage(hr, "CreateBuffer"); 
        return false;
	}

	return true;
}
//--------------------------------------------------------------------