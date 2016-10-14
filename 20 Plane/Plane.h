#pragma once

#include "D3D11/Buffer/VertexBuffer.h"
#include "D3D11/Shader/Shader.h"
#include "Utilities/Math/Vector3f.h"
#include "Graphics/Color4f.h"
//--------------------------------------------------------------------

class Plane
{
public:

	/*
		This function is called to initialize the plane.
	*/
	bool init();

	/*
		This function is called to generate a XZ-plane buffer centered at the origin.
			y (height)
			^
			|
		row	|  o
			|_ _ _> x (width)
			column
	*/
	bool generateColoredXYPlaneCenter(UINT row, UINT column, float width, float height, float zPosition = 0.0f);

	/*
		This function is called to generate a XZ-plane buffer centered at the origin.
			z (length)
			^
			|
		row	|  o
			|_ _ _> x (width)
			column
	*/
	bool generateColoredXZPlaneCenter(UINT row, UINT column, float width, float length, float yPosition = 0.0f);
	
	/*
		This function is called to draw the plane.
	*/
	void draw() const;

private:

	struct ColoredPlaneVertex
	{
		Vector3f vertex;
		Color4f color;
	};

	//	Buffer for the plane.
	VertexBuffer m_planeBuffer;

	//	Shader for the plane.
	Shader m_planeShader;
};
//--------------------------------------------------------------------

inline void Plane::draw() const
{
	m_planeShader.apply();
	m_planeBuffer.draw();
}
//--------------------------------------------------------------------