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

	if (!_obj.loadOBJFile("Obj/sphere.obj"))
		return false;
	
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/spotlight.fx", layout, numElements))
		return false;

	_texture.loadTexture2DFromFile("Texture/Earth.jpg");

	_camera.perspectiveProjectionFOV(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, -1.0f));

	_cameraCB.init(_camera.getCameraMatrix());

	_worldCB.init(nullptr, sizeof(Matrix44f));

	_light.create(Vector3f(10.0f, 0.0f, -10.0f), Color4f(0.8f, 0.2f, 0.2f));
	_lightCB.init(_light);

	_spotlightCB.init(_spotlightSource);

	debugMsg("Init Scene done\n");

	return true;
}
//--------------------------------------------------------------------

void Scene::update()
{
	_camera.updateInput(Input::get());

	if(Input::get()->isKeyOnPress('L'))
	{
		_light.toggle();
		_lightCB.updateData(_light);
	}
	if(Input::get()->isKeyOnPress('J'))
	{
		_light.updatePosition(-1.0f, 0.0f, 0.0f);
		_lightCB.updateData(_light);
	}
	else if(Input::get()->isKeyOnPress('K'))
	{
		_light.updatePosition(1.0f, 0.0f, 0.0f);
		_lightCB.updateData(_light);
	}
	if(Input::get()->isKeyOnPress('M'))
	{
		_spotlightSource.p++;
		_spotlightCB.init(_spotlightSource);
	}
	else if(Input::get()->isKeyOnPress('N'))
	{
		_spotlightSource.p--;
		_spotlightCB.init(_spotlightSource);
	}
}
//--------------------------------------------------------------------

void Scene::draw()
{
	_shader.apply();
	_texture.apply(0);
	_cameraCB.updateData(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);

	_lightCB.applyVS(2);
	_lightCB.applyPS(2);
	_spotlightCB.applyPS(3);


	_worldCB.updateData(matrixTranslation(0.5f, 2.0f, 10.0f));
	_worldCB.applyVS(1);
	_obj.draw();

	_worldCB.updateData(matrixTranslation(-5.0f, -0.5f, -5.0f));
	_worldCB.applyVS(1);
	_obj.draw();
}
//--------------------------------------------------------------------