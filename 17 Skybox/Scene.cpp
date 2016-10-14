#include "Scene.h"
#include "Core/Input.h"
#include "Utilities/Debug.h"
#include "D3D11/DxDevices.h"
//--------------------------------------------------------------------

Scene::Scene()
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	if (!_skybox.init("Texture/Snow.dds"))
		return false;

	_camera.perspectiveProjectionFOV(45.0f, 800.0f/600.0f, 0.1f, 1000.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, -1.0f));

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
	_cameraCB.updateData(_camera.getCameraMatrix());

	_skybox.draw(_cameraCB);
	
}
//--------------------------------------------------------------------