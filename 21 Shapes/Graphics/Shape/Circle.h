#pragma once

#include "Shape.h"
//--------------------------------------------------------------------

class Circle : public Shape
{
public:

	/*
		This function is called to generate a circle.
		at the XY-plane, centered at the origin.
	*/
	bool generateCircle(float radius = 1.0f, int slices = 20);
};
//--------------------------------------------------------------------