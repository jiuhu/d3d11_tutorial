#pragma once

#include "Shape.h"
//--------------------------------------------------------------------

class Mesh : public Shape
{
public:

	/*
		This function is called to load an OBJ from file.
	*/
	bool loadMeshFromOBJ(const char * const objFile, float scale = 1.0f, bool inverseTexture = true);
};
//--------------------------------------------------------------------