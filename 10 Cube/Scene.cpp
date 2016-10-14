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

	float vertices[] =
    { 
		//	Front
        -half, -half, -half,
        -half, half, -half,
        half, -half, -half,
		
        half, -half, -half,
        -half, half, -half,
        half, half, -half,
		
		//	Back
        half, -half, half,
        -half, half, half,
        -half, -half, half,
		
        half, half, half,
        -half, half, half,
        half, -half, half,

		//	Right
        half, -half, -half,
        half, half, -half,
        half, -half, half,
		
        half, -half, half,
        half, half, -half,
        half, half, half,

		//	Left
        -half, -half, half,
        -half, half, -half,
        -half, -half, -half,
		
        -half, half, half,
        -half, half, -half,
        -half, -half, half,

		//	Top
        -half, half, -half,
        -half, half, half,
        half, half, -half,
		
        half, half, -half,
        -half, half, half,
        half, half, half,

		//	Bottom
        half, -half, -half,
        -half, -half, half,
        -half, -half, -half,
		
        half, -half, half,
        -half, -half, half,
        half, -half, -half,
    };

	if (!_cube.loadVertexBuffer(vertices, 36, 3, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST))
		return false;
	
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/viewProjection.fx", layout, numElements))
		return false;


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
	_cameraCB.updateData(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);
	_cube.draw();
}
//--------------------------------------------------------------------