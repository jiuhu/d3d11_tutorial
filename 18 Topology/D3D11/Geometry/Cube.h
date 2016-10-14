#pragma once

#include "D3D11/Buffer/VertexBuffer.h"
//--------------------------------------------------------------------

class Cube : public VertexBuffer
{
public:

	/*
		This function is called to generate a cube centered at the origin.
	*/
	bool generateCube(float size = 1.0f, bool inverseNormal = false, bool reverseTexture = false);	

	/*
		This function is called to generate a cube centered at the origin.
	*/
	bool generateCubeVertexOnly(float size);	
};
//--------------------------------------------------------------------