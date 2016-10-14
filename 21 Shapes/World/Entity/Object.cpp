#include "Object.h"
#include "D3D11/DxDevices.h"
#include "Gfx3D.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

bool Object::init(Gfx3D &gfx, const Vector3f &position)
{	
	m_gfx = &gfx;
	m_position = position;
	m_size = 0.2f;
	m_size *= m_size;
	return true;
}
//--------------------------------------------------------------------

void Object::draw()
{
	DxDevices::_positioner.translation(m_position);
	m_gfx->draw();
	DxDevices::_positioner.pop();
}
//--------------------------------------------------------------------