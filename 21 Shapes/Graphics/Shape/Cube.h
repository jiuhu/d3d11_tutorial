#pragma once

#include "Shape.h"
//--------------------------------------------------------------------

class Cube : public Shape
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