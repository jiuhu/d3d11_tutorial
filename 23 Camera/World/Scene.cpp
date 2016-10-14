#include "Scene.h"
#include "Core/Input.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
#include "Utilities/Helper.h"
//--------------------------------------------------------------------

Scene::Scene()
	:	_isSolid(true),
		_font("Gothic")
{
	//	Empty
}
//--------------------------------------------------------------------

Scene::~Scene()
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	_devices = devices;

	
	//----------------------------------------
	//	Initialize Shader
	//----------------------------------------
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/world.fx", layout, numElements))
		return false;
	

	//----------------------------------------
	//	Initialize for GFX
	//----------------------------------------
	

	float size = 1.0f;

	_shape.loadMeshFromOBJ("Obj/sphere.obj");

	if(!_texture.loadTexture2DFromFile("Texture/Earth.jpg"))
		return false;
	

		
	
	//----------------------------------------
	//	Initialize the camera
	//----------------------------------------
	_camera.perspectiveProjectionFOV(60.0f, _devices->getAspectRatio(), 0.1f, 100.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, -5.0f), Vector3f(0.0f, 0.0f, 0.0f));
	
	_cameraCB.init(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);

	float w, h;
	_devices->getViewPort(w, h);
	_camera2D.orthoProjection(0.0f, w, h, 0.0f, -1.0f, 1.0f);
	_camera2D.lookAt(Vector3f(0.0f, 0.0f, -0.1f), Vector3f(0.0f, 0.0f, 0.0f));

	
	debugMsg("Init Scene done\n");

	return true;
}
//--------------------------------------------------------------------

void Scene::update()
{

	if(Input::get()->isKeyOnPress('M'))
	{
		_isSolid = !_isSolid;
		(_isSolid) ? _devices->polygonMode(D3D11_FILL_SOLID) : _devices->polygonMode(D3D11_FILL_WIREFRAME);
	}

	_camera.updateInput(Input::get());
	_cameraCB.updateData(_camera.getCameraMatrix());
}
//--------------------------------------------------------------------

void Scene::draw2D()
{
	_cameraCB.updateData(_camera2D.getCameraMatrix());
	
	_devices->enableBlend();

	_font.drawFormattedText(0.0f, 20.0f, "Eye : %.2f, %.2f, %.2f", _camera._eye.x, _camera._eye.y, _camera._eye.z);
	_font.drawFormattedText(0.0f, 40.0f, "Center : %.2f, %.2f, %.2f", _camera._center.x, _camera._center.y, _camera._center.z);
	_font.drawFormattedText(0.0f, 60.0f, "Up : %.2f, %.2f, %.2f", _camera._up.x, _camera._up.y, _camera._up.z);
	
	_devices->disableBlend();
}
//--------------------------------------------------------------------

void Scene::draw()
{	
	_cameraCB.updateData(_camera.getCameraMatrix());

	_shader.apply();

	_texture.apply(0);

	_shape.draw();
}
//--------------------------------------------------------------------