#pragma once

#include "Graphics/Color4f.h"
#include "Utilities/Math/Vector3f.h"
//--------------------------------------------------------------------

class Light
{
public:

	/*
		Constructor.
	*/
	Light();

	/*
		This function is called to create a light object with specified color.
	*/
	bool create(const Vector3f &position, const Color4f &diffuse, const Color4f &ambient = Color4f::black());

	/*
		This function is called to set the position by value.
	*/
	void setPosition(float x, float y, float z);

	/*
		This function is called to set the position by Vector.
	*/
	void setPosition(const Vector3f &position);

	/*
		This function is called to update the position by value.
	*/
	void updatePosition(float x, float y, float z);

	/*
		This function is called to update the position by Vector.
	*/
	void updatePosition(const Vector3f &position);

	/*
		This function is called to return the position.
	*/
	const Vector3f& getPosition() const;

	/*
		Set ambient with float values.
	*/
	void setAmbient(float r, float g, float b, float a = 1.0f);
	
	/*
		Set ambient with a Color4f object.
	*/
	void setAmbient(const Color4f &ambient);
	
	/*
		Return ambient color object.
	*/
	const Color4f& getAmbient() const;
	
	/*
		Set diffuse with float values.
	*/
	void setDiffuse(float r, float g, float b, float a = 1.0f);
	
	/*
		Set diffuse with a color object.
	*/
	void setDiffuse(const Color4f &diffuse);
	
	/*
		Return diffuse color object.
	*/
	const Color4f& getDiffuse() const;
	
	/*
		This function is called to toggle the light status.
	*/
	void toggle();


protected:

	//	Light On / Off status
	int m_lightStatus;

	//	Light position.
	Vector3f m_position;

	//	Light ambient color.
	Color4f m_ambient;
	
	//	Light diffuse color.
	Color4f m_diffuse;
};
//--------------------------------------------------------------------

inline void Light::setPosition(float x, float y, float z)
{
	m_position.set(x, y, z);
}
//--------------------------------------------------------------------

inline void Light::setPosition(const Vector3f &position)
{
	m_position = position;
}
//--------------------------------------------------------------------

inline void Light::updatePosition(float x, float y, float z)
{
	m_position.x += x;
	m_position.y += y;
	m_position.z += z;
}
//--------------------------------------------------------------------

inline void Light::updatePosition(const Vector3f &position)
{
	m_position += position;
}
//--------------------------------------------------------------------

inline const Vector3f& Light::getPosition() const
{
	return m_position;
}
//--------------------------------------------------------------------

inline void Light::setAmbient(float r, float g, float b, float a)
{ 
	m_ambient.setColor(r, g, b, a);
}
//--------------------------------------------------------------------

inline void Light::setAmbient(const Color4f &ambient) 
{ 
	m_ambient = ambient;
}
//--------------------------------------------------------------------

inline const Color4f& Light::getAmbient() const 
{ 
	return m_ambient; 
}
//--------------------------------------------------------------------

inline void Light::setDiffuse(float r, float g, float b, float a)
{ 
	m_diffuse.setColor(r, g, b, a); 
}
//--------------------------------------------------------------------

inline void Light::setDiffuse(const Color4f &diffuse)
{
	m_diffuse = diffuse;
}
//--------------------------------------------------------------------

inline const Color4f& Light::getDiffuse() const 
{
	return m_diffuse; 
}
//--------------------------------------------------------------------

inline void Light::toggle()
{
	m_lightStatus = !m_lightStatus;
}
//--------------------------------------------------------------------