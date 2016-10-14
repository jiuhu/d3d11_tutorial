#include "Quad.h"
#include "Shapes.h"
#include <vector>
//--------------------------------------------------------------------

bool Quad::generateQuadXYCenter(float top, float left, float bottom, float right)
{
	std::vector<Vertex3> vertices;
	vertices.push_back(Vertex3(left, bottom, 0.0f));
    vertices.push_back(Vertex3(left, top, 0.0f));
    vertices.push_back(Vertex3(right, bottom, 0.0f));
    vertices.push_back(Vertex3(right, top, 0.0f));
	
	return m_shapeBuffer.loadVertexBuffer((float*)&vertices[0], vertices.size(), 3, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
}
//--------------------------------------------------------------------

bool Quad::generateTexturedQuadXYCenter(float width, float height, bool hasNormal)
{
	float hWdith = width / 2.0f, hHeight = height / 2.0f;
	if (hasNormal)
	{
		std::vector<Vertex3Full> vertices;
		vertices.push_back(Vertex3Full(-hWdith, -hHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f));
		vertices.push_back(Vertex3Full(-hWdith, hHeight, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f));
		vertices.push_back(Vertex3Full(hWdith, -hHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f));
		vertices.push_back(Vertex3Full(hWdith, hHeight, 0.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f));
	
		return m_shapeBuffer.loadVertexBuffer((float*)&vertices[0], vertices.size(), 8, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
	else
	{
		std::vector<TexVertex3> vertices;
		vertices.push_back(TexVertex3(-hWdith, -hHeight, 0.0f, 0.0f, 0.0f));
		vertices.push_back(TexVertex3(-hWdith, hHeight, 0.0f, 0.0f, 1.0f));
		vertices.push_back(TexVertex3(hWdith, -hHeight, 0.0f, 1.0f, 0.0f));
		vertices.push_back(TexVertex3(hWdith, hHeight, 0.0f, 1.0f, 1.0f));
		
		return m_shapeBuffer.loadVertexBuffer((float*)&vertices[0], vertices.size(), 5, D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	}
}
//--------------------------------------------------------------------