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
	
	_plane.generateColoredXYPlaneCenter(8, 8, 8.0f, 8.0f);
	
	_camera.perspectiveProjectionFOV(45.0f, _devices->getAspectRatio(), 0.1f, 100.0f);
	_camera.lookAt(Vector3f(0.0f, -15.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f));
	

	_cameraCB.init(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);

	_worldCB.init(matrixIdentity());
	_worldCB.applyVS(1);

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
	_plane.draw();
}
//--------------------------------------------------------------------