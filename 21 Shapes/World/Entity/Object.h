#pragma once

#include "Utilities/Math/Vector3f.h"
//--------------------------------------------------------------------

class DxDevices;
class Gfx3D;
//--------------------------------------------------------------------

class Object
{
public:

	/*
		This function is called to initialize the object.
	*/
	bool init(Gfx3D &m_gfx, const Vector3f &position);

	/*
		This function is called to draw the object.
	*/
	void draw();

	/*
		This function is called to move the object manually.
	*/
	void move(float x, float y, float z);

	float getSize() const;

	//	World position of the object.
	const Vector3f& getPosition() const;
		
private:

	float m_size;

	//	World position of the object.
	Vector3f m_position;

	//	Pointer to the gfx object.
	Gfx3D * m_gfx;
};
//--------------------------------------------------------------------

inline void Object::move(float x, float y, float z)
{
	m_position.update(x, y, z);
}
//--------------------------------------------------------------------

inline const Vector3f& Object::getPosition() const
{
	return m_position;
}
//--------------------------------------------------------------------

inline float Object::getSize() const
{
	return m_size;
}
//--------------------------------------------------------------------

inline bool isCollide(const Object &o1, const Object &o2)
{
	float dist = distanceSq(o1.getPosition(), o2.getPosition());
	return (o1.getSize() + o2.getSize()) > dist;
}
//--------------------------------------------------------------------
