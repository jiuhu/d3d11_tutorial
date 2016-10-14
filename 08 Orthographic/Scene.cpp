#include "Scene.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

Scene::Scene()
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	float triangles[] =
    {
        100.0f, 40.0f, 0.0f,
        120.0f, 80.0f, 0.0f,
        80.0f, 80.0f, 0.0f,
    };
	if (!_triangle.loadVertexBuffer(triangles, 3))
		return false;
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/viewProjection.fx", layout, numElements))
		return false;

	_camera.orthoProjection(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, 0.1f), Vector3f(0.0f, 0.0f, 0.0f));
	//_camera.initOrtho(800.0f, 600.0f, -1.0f, 1.0f, Vector3f(0.0f, 0.0f, 0.1f));
	_cameraCB.init(_camera.getCameraMatrix());

	debugMsg("Init Scene done\n");

	return true;
}
//--------------------------------------------------------------------

void Scene::update()
{
}
//--------------------------------------------------------------------

void Scene::draw()
{
	_shader.apply();
	_cameraCB.updateData(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);
	_triangle.draw();
}
//--------------------------------------------------------------------