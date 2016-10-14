#pragma once

#include "D3D11/Buffer/VertexBuffer.h"
#include "D3D11/Buffer/ConstantBuffer.h"
#include "D3D11/Shader/Shader.h"
#include "D3D11/Texture/Texture.h"
#include "Graphics/Camera.h"
#include "Entity/SkyBox.h"
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
	Shader _shaderNormal;
	
	VertexBuffer _obj;

	ConstantBuffer _cameraCB;

	ConstantBuffer _worldCB;

	Camera _camera;

	Texture _texture;

	SkyBox _box;
};
//--------------------------------------------------------------------