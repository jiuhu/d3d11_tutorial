#include "Circle.h"
#include "Shapes.h"
#include <vector>
#include "Utilities/Math/MyMath.h"
//--------------------------------------------------------------------

bool Circle::generateCircle(float radius, int slices)
{
	std::vector<Vertex3> vertices;
	float radian = 0.0f, step = TwoPI / slices;
	for (int i = 0; i <= slices; ++i, radian += step)
		vertices.push_back(Vertex3(sin(radian), cos(radian), 0.0f));

	return m_shapeBuffer.loadVertexBuffer((float*)&vertices[0], vertices.size(), 3, D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
}
//--------------------------------------------------------------------