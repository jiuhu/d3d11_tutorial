#pragma once

#include "Shape.h"
//--------------------------------------------------------------------

class Disk : public Shape
{
public:

	/*
		This function is called to generate a disk.
		at the XY-plane, centered at the origin.
	*/
	bool generateDisk(float radius = 1.0f, int slices = 20);
};
//--------------------------------------------------------------------