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
	_box.init("Texture/snow.dds");

	if (!_obj.loadVertexBufferFromOBJFile("Obj/dodecahedron.obj"))
		return false;
	
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/world.fx", layout, numElements))
		return false;

	
    D3D11_INPUT_ELEMENT_DESC layout2[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	numElements = ARRAYSIZE( layout2 );
	if (!_shaderNormal.loadShaderFromFX("Shaders/displayNormal.fx", layout2, numElements, true))
		return false;

	_texture.loadTexture2DFromFile("Texture/Earth.jpg");

	_camera.perspectiveProjectionFOV(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, 10.0f), Vector3f(0.0f, 0.0f, -1.0f));

	_cameraCB.init(_camera.getCameraMatrix());

	_worldCB.init(matrixIdentity());

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
	_texture.apply(0);

	_cameraCB.updateData(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);

	_worldCB.applyVS(1);

	_shaderNormal.apply();
	_obj.draw();
	
	_shader.apply();
	_obj.draw();



	_box.draw();

}
//--------------------------------------------------------------------