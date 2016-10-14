#include "PhongLight.h"
//--------------------------------------------------------------------

PhongLight::PhongLight()
	:	m_specular(Color4f::white())
{
	//	Empty
}
//--------------------------------------------------------------------

bool PhongLight::create(const Vector3f &position, const Color4f &diffuse, const Color4f &ambient, const Color4f &specular) 
{
	setPosition(position);
	
	setDiffuse(diffuse);
	
	setAmbient(ambient);
	
	setSpecular(specular);

	return true;
}
//--------------------------------------------------------------------