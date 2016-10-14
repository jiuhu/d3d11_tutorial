#pragma once

#include "D3D11/Buffer/ConstantBuffer.h"
#include "D3D11/Shader/Shader.h"
#include "D3D11/Texture/Texture.h"
#include "Graphics/Camera.h"
#include "Graphics/Shapes/Mesh.h"
#include "D3D11/Font/Font.h"
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
		Destructor.
	*/
	~Scene();

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
	void draw2D();

	/*
		This function is called to draw the world.
	*/
	void draw();
	
private:
	DxDevices * _devices;

	bool _isSolid;
	
	Camera _camera;
	Camera _camera2D;
	ConstantBuffer _cameraCB;
	
	Shader _shader;
	

	Mesh _shape;
	Texture _texture;

	Font _font;
};
//--------------------------------------------------------------------