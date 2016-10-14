#include "Scene.h"
#include "D3D11/DxDevices.h"
#include "Core/Input.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

Scene::Scene()
	:	_blendOn(false)
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	_devices = devices;

	float triangles[] =
    {
        0.0f, 0.2f, 0.5f,
        0.2f, -0.2f, 0.5f,
        -0.2f, -0.2f, 0.5f,
    };
	if (!_triangle.loadVertexBuffer(triangles, 3))
		return false;

	float quads[] =
    {
		/*	Cull None
			0---2
			|	|
			1---3
		*/
        -0.5f, 0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
    };
	if (!_quad.loadVertexBuffer(quads, 4, 3, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP))
		return false;
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/color.fx", layout, numElements))
		return false;


	float color[] = { 1.0f, 1.0f, 0.0f, 1.0f };
	_colorCB.init(color);

	debugMsg("Init Scene done\n");

	return true;
}
//--------------------------------------------------------------------

void Scene::update()
{
	if (Input::get()->isKeyOnPress('B'))
		_blendOn = !_blendOn;
}
//--------------------------------------------------------------------

void Scene::draw()
{
	_shader.apply();
	
	float color2[] = { 1.0f, 0.0f, 1.0f, 1.0f };
	_colorCB.updateData(color2);
	_colorCB.applyPS(0);
	_triangle.draw();

	float color[] = { 1.0f, 1.0f, 1.0f, 0.5f };
	_colorCB.updateData(color);
	_colorCB.applyPS(0);
	if (_blendOn)
	{
		_devices->enableBlend();
		_quad.draw();
		_devices->disableBlend();
	}
	else
		_quad.draw();
}
//--------------------------------------------------------------------