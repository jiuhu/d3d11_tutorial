#pragma once

#include "D3D11/Shader/Shader.h"
#include "D3D11/Buffer/ConstantBuffer.h"
#include "Graphics/Camera.h"
#include "Plane.h"
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

	Shader _shader;
	
	Plane _plane;

	ConstantBuffer _cameraCB;

	ConstantBuffer _worldCB;

	Camera _camera;
};
//--------------------------------------------------------------------