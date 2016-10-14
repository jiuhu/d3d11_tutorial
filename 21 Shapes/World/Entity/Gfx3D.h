#pragma once

#include "Graphics/Shape/Shape.h"
//--------------------------------------------------------------------

class Texture;
//--------------------------------------------------------------------

class Gfx3D : public Shape
{
public:

	Gfx3D();

	/*
		This function is called to initialize the 3D gfx object.
	*/
	bool init(VertexBuffer &shape, Texture &texture);

	/*
		This function is called to draw the 3D gfx object.
	*/
	virtual void draw() const;
		
private:

	//	Pointer to the texture.
	Texture * m_texture;
};
//--------------------------------------------------------------------