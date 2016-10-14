#include "Plane.h"
#include "Utilities/Debug.h"
#include <vector>
//--------------------------------------------------------------------

bool Plane::init()
{
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!m_planeShader.loadShaderFromFX("Shaders/plane.fx", layout, numElements))
		return false;

	return true;
}
//--------------------------------------------------------------------


//bool Plane::generateXYPlaneVertexOnly(const Vector3f &start, UINT row, UINT column, float size)
//{
//	std::vector<float> vertices;
//	std::vector<UINT> indices;
//	float width = size / row, height = size / column;
//	
//	for (float i = -1, r = start.y; i++ < row; r += height)
//	{
//		for (float j = -1, c = start.x; j++ < column; c += width)
//		{
//			vertices.push_back(c);
//			vertices.push_back(r);
//			vertices.push_back(start.z);
//		}
//	}
//	
//	indices.push_back(0);
//	int col = column + 1;
//	for (UINT i = 0; i < row; i++)
//	{
//		int current = i * col,
//			next = (i + 1) * col;
//		//	--->
//		if (i%2==0)
//		{
//			indices.push_back(next);
//			for (UINT j = 1; j <= column; j++)
//			{
//				indices.push_back(current + j);
//				indices.push_back(next + j);
//			}
//		}
//		//	<---
//		else
//		{
//			indices.push_back(next + column);
//			for (UINT j = column - 1; j >= 0; j--)
//			{
//				indices.push_back(current + j);			
//				indices.push_back(next + j);
//			}
//		}
//	}
//
//	if (!loadIndexedBuffer(&vertices[0], vertices.size()/3, &indices[0], indices.size(), 3, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP))
//		return false;
//
//	return true;
//}
////--------------------------------------------------------------------

//bool Plane::generateXZPlaneColored(const Vector3f &start, UINT row, UINT column, float size)
//{
//	float width = size / row, height = size / column,
//			currentY = start.y, currentX, nextX, nextY;
//	
//	std::vector<PlaneVertex> vertices;
//	PlaneVertex pv;
//	pv.vertex = start;
//	for (UINT r = 0; r < row; ++r)
//	{
//		currentX = start.x;
//		nextY = currentY + height;
//		for (UINT c = 0; c < column; ++c)
//		{
//			if (((c + r) % 2) == 0)
//				pv.color = Color4f::blue();
//			else
//				pv.color = Color4f::yellow();
//
//			nextX = currentX + width;
//
//			pv.vertex.x = currentX;
//			pv.vertex.y = currentY;
//			vertices.push_back(pv);
//			
//			pv.vertex.y = nextY;
//			vertices.push_back(pv);
//
//			pv.vertex.x = nextX;
//			pv.vertex.y = currentY;
//			vertices.push_back(pv);
//			vertices.push_back(pv);
//
//			pv.vertex.x = currentX;
//			pv.vertex.y = nextY;
//			vertices.push_back(pv);
//
//			pv.vertex.x = nextX;
//			vertices.push_back(pv);
//
//			currentX = nextX;
//		}
//		currentY = nextY;
//	}
//
//	if (!loadVertexBuffer((float *)&vertices[0], vertices.size(), 7))
//		return false;
//
//	return true;
//}
////--------------------------------------------------------------------

bool Plane::generateColoredXYPlaneCenter(UINT row, UINT column, float width, float height, float zPosition)
{
	float	cellWidth = width / column, cellHeight = height / row,
			startX = width / -2.0f, startZ = height / -2.0f,
			currentY = startZ, currentX, nextX, nextY;
	
	std::vector<ColoredPlaneVertex> vertices;
	ColoredPlaneVertex pv;
	pv.vertex.z = zPosition;
	for (UINT r = 0; r < row; ++r)
	{
		currentX = startX;
		nextY = currentY + cellHeight;
		for (UINT c = 0; c < column; ++c)
		{
			if (((c + r) % 2) == 0)
				pv.color = Color4f::blue();
			else
				pv.color = Color4f::yellow();

			nextX = currentX + cellWidth;

			pv.vertex.x = currentX;
			pv.vertex.y = currentY;
			vertices.push_back(pv);
			
			pv.vertex.y = nextY;
			vertices.push_back(pv);

			pv.vertex.x = nextX;
			pv.vertex.y = currentY;
			vertices.push_back(pv);
			vertices.push_back(pv);

			pv.vertex.x = currentX;
			pv.vertex.y = nextY;
			vertices.push_back(pv);

			pv.vertex.x = nextX;
			vertices.push_back(pv);

			currentX = nextX;
		}
		currentY = nextY;
	}

	if (!m_planeBuffer.loadVertexBuffer((float *)&vertices[0], vertices.size(), 7))
		return false;

	return init();
}
//--------------------------------------------------------------------

bool Plane::generateColoredXZPlaneCenter(UINT row, UINT column, float width, float length, float yPosition)
{
	float	cellWidth = width / column, cellLength = length / row,
			startX = width / -2.0f, startZ = length / -2.0f,
			currentZ = startZ, currentX, nextX, nextZ;
	
	std::vector<ColoredPlaneVertex> vertices;
	ColoredPlaneVertex pv;
	pv.vertex.y = yPosition;
	for (UINT r = 0; r < row; ++r)
	{
		currentX = startX;
		nextZ = currentZ + cellLength;
		for (UINT c = 0; c < column; ++c)
		{
			if (((c + r) % 2) == 0)
				pv.color = Color4f::blue();
			else
				pv.color = Color4f::yellow();

			nextX = currentX + cellWidth;

			pv.vertex.x = currentX;
			pv.vertex.z = currentZ;
			vertices.push_back(pv);
			
			pv.vertex.z = nextZ;
			vertices.push_back(pv);

			pv.vertex.x = nextX;
			pv.vertex.z = currentZ;
			vertices.push_back(pv);
			vertices.push_back(pv);

			pv.vertex.x = currentX;
			pv.vertex.z = nextZ;
			vertices.push_back(pv);

			pv.vertex.x = nextX;
			vertices.push_back(pv);

			currentX = nextX;
		}
		currentZ = nextZ;
	}

	if (!m_planeBuffer.loadVertexBuffer((float *)&vertices[0], vertices.size(), 7))
		return false;

	return init();
}
//--------------------------------------------------------------------