#include "Scene.h"
#include "Core/Input.h"
#include "Utilities/Debug.h"
#include <vector>
//--------------------------------------------------------------------

Scene::Scene()
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	float size = 1.0f;
	
	float half = size / 2.0f;
	bool reverseTexture = true;
	float texZero = (reverseTexture) ? 1.0f : 0.0f;
	float texOne = (reverseTexture) ? 0.0f : 1.0f;

	float vertices[] =
    { 
		//	Front
        -half, -half, -half,	0.0f, texZero,
        -half, half, -half,		0.0f, texOne,
        half, -half, -half,		1.0f, texZero,
		
        half, -half, -half,		1.0f, texZero,
        -half, half, -half,		0.0f, texOne,
        half, half, -half,		1.0f, texOne,
		
		//	Back
        half, -half, half,		0.0f, texZero,
        half, half, half,		0.0f, texOne,
        -half, -half, half,		1.0f, texZero,
		
        -half, -half, half,		1.0f, texZero,
        half, half, half,		0.0f, texOne,
        -half, half, half,		1.0f, texOne,

		//	Left
        half, -half, -half,		0.0f, texZero,
        half, half, -half,		0.0f, texOne,
        half, -half, half,		1.0f, texZero,
		
        half, -half, half,		1.0f, texZero,
        half, half, -half,		0.0f, texOne,
        half, half, half,		1.0f, texOne,

		//	Right
        -half, -half, half,		0.0f, texZero,
        -half, half, half,		0.0f, texOne,
        -half, -half, -half,	1.0f, texZero,
		
        -half, -half, -half,	1.0f, texZero,
        -half, half, half,		0.0f, texOne,
        -half, half, -half,		1.0f, texOne,

		//	Top
        -half, half, -half,		0.0f, texZero,
        -half, half, half,		0.0f, texOne,
        half, half, -half,		1.0f, texZero,
		
        half, half, -half,		1.0f, texZero,
        -half, half, half,		0.0f, texOne,
        half, half, half,		1.0f, texOne,

		//	Bottom
        half, -half, -half,		1.0f, texZero,
        -half, -half, half,		0.0f, texOne,
        -half, -half, -half,	0.0f, texZero,
		
        half, -half, half,		1.0f, texOne,
        -half, -half, half,		0.0f, texOne,
        half, -half, -half,		1.0f, texZero,
    };

	if (!_cube.loadVertexBuffer(vertices, 36, false, true, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST))
		return false;
	
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/texture.fx", layout, numElements))
		return false;

	_texture.loadTexture2DFromFile("Texture/Earth.jpg");

	_camera.perspectiveProjectionFOV(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 10.0f));

	_cameraCB.init(_camera.getCameraMatrix());

	debugMsg("Init Scene done\n");

	return true;
}
//--------------------------------------------------------------------

void Scene::update()
{
	_camera.updateInput(Input::get());
}
//--------------------------------------------------------------------

void Scene::draw()
{
	_shader.apply();
	_texture.apply(0);
	_cameraCB.updateData(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);
	_cube.draw();
}
//--------------------------------------------------------------------