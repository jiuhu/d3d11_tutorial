#include "Scene.h"
#include "Core/Input.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

Scene::Scene()
	:	_isSolid(true),
		_topology(0)
{
}
//--------------------------------------------------------------------

	
unsigned int indices[][12] =
{
	{ 0, 1, 2, 3, 4, 5, 6, 7, 8 },
	{ 0, 4, 1, 5, 3, 6, 7, 8 },
	{ 0, 1, 2, 5, 8, 7, 6, 3 },
	{ 3, 0, 1, 1, 2, 5, 6, 3, 7, 7, 5, 8 },
	{ 3, 0, 4, 1, 5, 2},
	{ 3, 0, 1, 6, 4, 2, 5, 7, 8, }
};

bool Scene::init(DxDevices * devices)
{
	_devices = devices;

	float vertices[] =
    {
		-0.5f, 0.5f,
		0.0f, 0.5f,
		0.5f, 0.5f,
		
		-0.5f, 0.0f,
		0.0f, 0.0f,
		0.5f, 0.0f,
		
		-0.5f, -0.5f,
		0.0f, -0.5f,
		0.5f, -0.5f,
    };

	if (!_buffer.loadIndexedBuffer(vertices, 9, indices[0], 9, 2, D3D_PRIMITIVE_TOPOLOGY_POINTLIST))
		return false;

	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	if (!_shader.loadShaderFromFX("Shaders/vertex.fx", layout, 1))
		return false;

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

	
	if(Input::get()->isKeyOnPress('T'))
	{
		_topology++;
		switch(_topology)
		{
		case 0:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_POINTLIST);
			_buffer.loadIndexBuffer(indices[0], 9);
			break;

		case 1:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
			_buffer.loadIndexBuffer(indices[1], 8);
			break;

		case 2:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST_ADJ);
			break;

		case 3:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP);
			_buffer.loadIndexBuffer(indices[2], 8);
			break;

		case 4:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINESTRIP_ADJ);
			break;

		case 5:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
			_buffer.loadIndexBuffer(indices[3], 12);
			break;

		case 6:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST_ADJ);
			break;

		case 7:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
			_buffer.loadIndexBuffer(indices[4], 6);
			break;

		case 8:
			_buffer.setPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP_ADJ);
			_buffer.loadIndexBuffer(indices[5], 9);
			_topology = -1;
			break;
		}
	}

}
//--------------------------------------------------------------------

void Scene::draw()
{
	_shader.apply();
	_buffer.drawIndexed();
}
//--------------------------------------------------------------------