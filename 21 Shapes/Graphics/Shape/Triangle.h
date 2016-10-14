#pragma once

#include "Shape.h"
//--------------------------------------------------------------------

class Triangle : public Shape
{
public:

	/*
		This function is called to generate an equilateral triangle.
		at the XY-plane, centered at the origin.
	*/
	bool generateTriangle(float size = 1.0f);
};
//--------------------------------------------------------------------