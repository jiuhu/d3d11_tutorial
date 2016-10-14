#include "Scene.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

Scene::Scene()
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{

	float vertices[] =
    {
        0.0f, 0.5f, 0.5f,
        0.5f, -0.5f, 0.5f,
        -0.5f, -0.5f, 0.5f,
    };
	if (!_buffer.loadVertexBuffer(vertices, 3))
		return false;

	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/vertex.fx", layout, numElements))
		return false;

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
	_buffer.draw();
}
//--------------------------------------------------------------------