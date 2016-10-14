#pragma once

#include "Shape.h"
//--------------------------------------------------------------------

class Quad : public Shape
{
public:

	/*
		This function is called to generate a quad at the XY-plane.
		(left, top)
			x - - 
			|    |
			|    |
			 - - x
				(right, bottom)
	*/
	bool generateQuadXYCenter(float top, float left, float bottom, float right);

	/*
		This function is called to generate a quad.
		at the XY-plane, centered at the origin.
	*/
	bool generateQuadXYCenter(float width = 1.0f, float height = 1.0f)
	{
		float hWidth = width / 2.0f, hHeight = height / 2.0f;
		return generateQuadXYCenter(hHeight, -hWidth, -hHeight, hWidth);
	}

	/*
		This function is called to generate a quad starting from the origin.
			 - - -	(widthm height)
			|    |
			|    |
			x - - -
		(0, 0)
	*/
	bool generateQuadXY(float width = 1.0f, float height = 1.0f)
	{
		return generateQuadXYCenter(height, 0.0f, 0.0f, width);
	}

	/*
		This function is called to generate a textured quad.
		at the XY-plane, centered at the origin.
	*/
	bool generateTexturedQuadXYCenter(float width = 1.0f, float height = 1.0f, bool hasNormal = false);
};
//--------------------------------------------------------------------