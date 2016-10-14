#pragma once

#include "Graphics/Geometry/Cube.h"
#include "D3D11/Texture/Texture.h"
#include "Utilities/Math/Matrix44f.h"
//--------------------------------------------------------------------

class DxDevices;
//--------------------------------------------------------------------

class BigBox
{
public:

	/*
		This function is called to initialize the skybox.
	*/
	bool init(LPCSTR textureFile, float size = 50.0f);

	/*
		This function is called to draw the skybox.
	*/
	void draw(DxDevices * devices);

	Matrix44f m_world;
	
private:

	//	The skybox cube object
	Cube m_box;

	//	Texture for the skybox.
	Texture m_texture;
};
//--------------------------------------------------------------------