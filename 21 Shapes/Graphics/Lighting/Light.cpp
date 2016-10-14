#include "Light.h"
//--------------------------------------------------------------------

Light::Light()
	:	m_lightStatus(1),
		m_position(), 
		m_diffuse(Color4f::white()), 
		m_ambient(Color4f::black())
{
	//	Empty
}
//--------------------------------------------------------------------

bool Light::create(const Vector3f &position, const Color4f &diffuse, const Color4f &ambient) 
{
	setPosition(position);
	
	setDiffuse(diffuse);
	
	setAmbient(ambient);

	return true;
}
//--------------------------------------------------------------------