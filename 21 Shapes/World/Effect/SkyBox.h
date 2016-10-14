#pragma once

#include "Graphics/Geometry/Cube.h"
#include "D3D11/Shader/Shader.h"
#include "D3D11/Texture/Texture.h"
//--------------------------------------------------------------------

class SkyBox
{
public:

	/*
		This function is called to initialize the skybox.
	*/
	bool init(LPCSTR textureFile, float size = 50.0f);

	/*
		This function is called to draw the skybox.
	*/
	void draw();
	
private:

	//	The skybox cube object
	Cube m_box;

	//	Shader effect for the sky box.
	Shader m_shader;

	//	Texture for the skybox.
	Texture m_texture;
};
//--------------------------------------------------------------------