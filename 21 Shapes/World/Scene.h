#pragma once

#include "D3D11/Buffer/ConstantBuffer.h"
#include "D3D11/Shader/Shader.h"
#include "D3D11/Texture/Texture.h"
#include "Graphics/Camera.h"
#include "Graphics/Shape/Triangle.h"
#include "Graphics/Shape/Quad.h"
#include "Graphics/Shape/Circle.h"
#include "Graphics/Shape/Disk.h"
#include "Graphics/Shape/Cube.h"
#include "Graphics/Shape/Mesh.h"
//--------------------------------------------------------------------

class DxDevices;
//--------------------------------------------------------------------

class Scene
{
public:

	/*
		Constructor.
	*/
	Scene();

	/*
		This function is called to initialize the world.
	*/
	bool init(DxDevices * devices);

	/*
		This function is called to update the world.
	*/
	void update();

	/*
		This function is called to draw 2D element of the world.
		Eg. Drawing text
	*/
	void draw();
	
private:
	DxDevices * _devices;

	bool _isSolid;
	
	Camera _camera;
	ConstantBuffer _cameraCB;
	
	Shader _shader;

	Triangle _tri;

	Quad _quad;

	Circle _circle;

	Disk _disk;

	Cube _cube;

	Mesh _mesh;
};
//--------------------------------------------------------------------