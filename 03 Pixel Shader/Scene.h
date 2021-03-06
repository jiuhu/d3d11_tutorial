#pragma once

#include "D3D11/Buffer/VertexBuffer.h"
#include "D3D11/Shader/Shader.h"
//--------------------------------------------------------------------

class DxDevices;
class WinInputDevice;
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

	Shader _shader;
	
	VertexBuffer _buffer;
};
//--------------------------------------------------------------------