#pragma once

#include "Light.h"
//--------------------------------------------------------------------

class PhongLight : public Light
{
public:

	/*
		Constructor.
	*/
	PhongLight();

	/*
		This function is called to create a PhongLight object with specified color.
	*/
	bool create(const Vector3f &position, const Color4f &diffuse,
				const Color4f &ambient = Color4f::black(), const Color4f &specular = Color4f::white());

	/*
		Set diffuse with float values.
	*/
	void setSpecular(float r, float g, float b, float a = 1.0f);
	
	/*
		Set diffuse with color object.
	*/
	void setSpecular(const Color4f &specular);
	
	/*
		Return specular color object.
	*/
	const Color4f& getSpecular() const;

protected:
	
	//	PhongLight specular color.
	Color4f m_specular;
};
//--------------------------------------------------------------------

inline void PhongLight::setSpecular(float r, float g, float b, float a)
{ 
	m_specular.setColor(r, g, b, a);
}
//--------------------------------------------------------------------

inline void PhongLight::setSpecular(const Color4f &specular) 
{
	m_specular = specular;
}
//--------------------------------------------------------------------

inline const Color4f& PhongLight::getSpecular() const 
{
	return m_specular; 
}
//--------------------------------------------------------------------