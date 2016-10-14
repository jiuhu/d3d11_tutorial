#pragma once

#include "D3D11/Buffer/ConstantBuffer.h"
#include "D3D11/Shader/Shader.h"
#include "D3D11/Texture/Texture.h"
#include "Graphics/Camera.h"
#include "Graphics/Font.h"
#include "Graphics/Shape/Quad.h"
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

	Font _font;

	VertexBuffer _buffer;
};
//--------------------------------------------------------------------