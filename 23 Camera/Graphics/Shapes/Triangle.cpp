#include "Triangle.h"
#include <cmath>
//--------------------------------------------------------------------

bool Triangle::generateTriangle(float size)
{
	float width = sqrt(size / 3.0f), height = size / 2.0f;
	float vertices[] =
    {
        0.0f, height, 0.0f,
        width, -height, 0.0f,
        -width, -height, 0.0f,
    };
	
	return m_shapeBuffer.loadVertexBuffer(vertices, 3, 3);
}
//--------------------------------------------------------------------