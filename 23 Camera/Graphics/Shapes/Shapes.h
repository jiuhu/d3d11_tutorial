#pragma once

/*
	Aims to assist for vertices generation.
	Should only be use under implementation.
	Not recommended to use in header.
*/

class Vertex2
{
public:

	Vertex2() { }

	Vertex2(float x, float y)
		:	_x(x), _y(y)
	{ }
	
	float _x, _y;
};
//--------------------------------------------------------------------

class Vertex3
{
public:

	Vertex3() { }

	Vertex3(float x, float y, float z)
		:	_x(x), _y(y), _z(z)
	{ }

	float _x, _y, _z;
};
//--------------------------------------------------------------------

class TexCoord
{
public:

	TexCoord() { }

	TexCoord(float u, float v)
		:	_u(u), _v(v)
	{ }
	
	float _u, _v;
};
//--------------------------------------------------------------------

class TexVertex3
{
public:

	TexVertex3() { }

	TexVertex3(float x, float y, float z, float u, float v)
		:	_v(x, y, z), _t(u, v)
	{ }
	
	Vertex3 _v;
	TexCoord _t;
};
//--------------------------------------------------------------------

class Vertex3Full
{
public:

	Vertex3Full() { }

	Vertex3Full(float x, float y, float z, float nX, float nY, float nZ, float u, float v)
		:	_v(x, y, z), _n(nX, nY, nZ), _t(u, v)
	{ }
	
	Vertex3 _v;
	Vertex3 _n;
	TexCoord _t;
};
//--------------------------------------------------------------------

class VertexFont
{
public:

	VertexFont() { }

	VertexFont(float x, float y, float u, float v)
		:	_v(x, y), _t(u, v)
	{ }

	VertexFont(const Vertex2 &v, const TexCoord &t)
		:	_v(v), _t(t)
	{ }
	
	Vertex2 _v;
	TexCoord _t;
};
//--------------------------------------------------------------------

class TexCoordFont
{
public:

	TexCoordFont() { }

	TexCoordFont(const TexCoord &t0, const TexCoord &t1, const TexCoord &t2, const TexCoord &t3)
	{ 
		_t[0] = t0;
		_t[1] = t1;
		_t[2] = t2;
		_t[3] = t3;
	}
	
	TexCoord _t[4];
};
//--------------------------------------------------------------------