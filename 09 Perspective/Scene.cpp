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
	float size = 1.0f;
	float ground = -1.0f;
	//float quads[] =
 //   {
	//	/*	Cull None
	//		0---2
	//		|	|
	//		1---3
	//	*/
 //       //0.0f, 100.0f, 0.0f,
 //       //0.0f, 0.0f, 0.0f,
 //       //100.0f, 100.0f, 0.0f,
 //       //100.0f, 0.0f, 0.0f,

	//	
 //       -size, y, size,
 //       -size, y, -size,
 //       size, y, size,
 //       size, y, -size,
 //   };

	int row = 8, column = 8,
		totalLines = row + column + 2;

	std::vector<float> board;
	board.reserve(totalLines * 4);
		
	//	Default offset
	float startX = (row / 2) * -size, startZ = startX,
	//	Default end point
		endX = startX + (size * column), endZ = startZ + (size * row),
	//	Temp storage
		x = startX, z = startZ;
		
	//	First generate rows
	for (int i = 0; i <= row; i++)
	{
		board.push_back(startX);
		board.push_back(ground);
		board.push_back(z);
		board.push_back(endX);
		board.push_back(ground);
		board.push_back(z);
		z += size;
	}

	//	Then generate columns
	for (int i = 0; i <= column; i++)
	{
		board.push_back(x);
		board.push_back(ground);
		board.push_back(startZ);
		board.push_back(x);
		board.push_back(ground);
		board.push_back(endZ);
		x += size;
	}




	if (!_plane.loadVertexBuffer(&board[0], (totalLines * 2), 3, D3D11_PRIMITIVE_TOPOLOGY_LINELIST))
		return false;
	
	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/viewProjection.fx", layout, numElements))
		return false;


	_camera.perspectiveProjectionFOV(45.0f, 800.0f/600.0f, 0.1f, 100.0f);
	_camera.lookAt(Vector3f(0.0f, 0.0f, 0.0f), Vector3f(0.0f, 0.0f, 10.0f));

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
	_shader.apply();
	_cameraCB.updateData(_camera.getCameraMatrix());
	_cameraCB.applyVS(0);
	_plane.draw();
}
//--------------------------------------------------------------------