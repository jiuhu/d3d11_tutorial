#include "Scene.h"
#include "Core/Input.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
#include <vector>
//--------------------------------------------------------------------

Scene::Scene()
	:	_isSolid(true)
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	_devices = devices;
	
	//----------------------------------------
	//	Initialize the camera
	//----------------------------------------
	_camera.perspectiveProjectionFOV(45.0f, _devices->getAspectRatio(), 0.1f, 1000.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f));
	

	_cameraCB.init(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);

	
	//----------------------------------------
	//	Initialize Shader
	//----------------------------------------
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        //{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        //{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/viewProjection.fx", layout, numElements))
		return false;

	
	//----------------------------------------
	//	Initialize Shapes
	//----------------------------------------

	//_tri.generateTriangle();
	//
	_quad.generateQuadXY();

	//_circle.generateCircle();

	//_disk.generateDisk();

	//_cube.generateCubeVertexOnly(1.0f);

	//_mesh.loadMeshFromOBJ("obj/sphere.obj");
	
	debugMsg("Init Scene done\n");

	return true;
}
//--------------------------------------------------------------------

void Scene::update()
{
	_camera.updateInput(Input::get());
	_cameraCB.updateData(_camera.getCameraMatrix());

	if(Input::get()->isKeyOnPress('M'))
	{
		_isSolid = !_isSolid;
		(_isSolid) ? _devices->polygonMode(D3D11_FILL_SOLID) : _devices->polygonMode(D3D11_FILL_WIREFRAME);
	}

}
//--------------------------------------------------------------------

void Scene::draw()
{
	_shader.apply();

	_quad.draw();
	//_tri.draw();
	//_disk.draw();
	//_cube.draw();
	//_mesh.draw();
}
//--------------------------------------------------------------------