#include "Gfx3D.h"
#include "D3D11/Buffer/VertexBuffer.h"
#include "D3D11/Texture/Texture.h"
//--------------------------------------------------------------------

Gfx3D::Gfx3D()
	:	m_texture(nullptr) 
{
	//	Empty
}
//--------------------------------------------------------------------

bool Gfx3D::init(VertexBuffer &shape, Texture &texture)
{	
	m_shape = &shape;
	m_texture = &texture;
	return true;
}
//--------------------------------------------------------------------

void Gfx3D::draw() const
{
	m_texture->apply(0);

	m_shape->draw();
}
//--------------------------------------------------------------------