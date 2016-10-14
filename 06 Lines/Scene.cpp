#include "Scene.h"
#include "Utilities/Debug.h"
#include "D3D11/DxDevices.h"
//--------------------------------------------------------------------

Scene::Scene()
{
}
//--------------------------------------------------------------------

bool Scene::init(DxDevices * devices)
{
	struct CBuffer
	{
		int rangeX;
		int rangeY;
		float origin[2];
	};
	CBuffer cb;
	cb.rangeX = 10;
	cb.rangeY = 10;
	cb.origin[0] = -0.6f;
	cb.origin[1] = -0.6f;
	
	float vertices[] =
    {
		//	X-axis
        //-0.5f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
        //0.5f, 0.0f, 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		-0.8f, cb.origin[1], 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		0.8f, cb.origin[1], 0.0f,	1.0f, 0.0f, 0.0f, 1.0f,
		//	Y-axis
        //0.0f, -0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
        //0.0f, 0.5f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
        cb.origin[0], -0.8f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
        cb.origin[0], 0.8f, 0.0f,	0.0f, 1.0f, 0.0f, 1.0f,
		//	Z-axis
        //0.0f, 0.0f, 0.5f,	0.0f, 0.0f, 1.0f, 1.0f,
        //0.0f, 0.0f, -0.5f,	0.0f, 0.0f, 1.0f, 1.0f,
    };
	if (!_buffer.loadColorVertexBuffer(vertices, 4, false, D3D_PRIMITIVE_TOPOLOGY_LINELIST))
		return false;

	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	UINT numElements = ARRAYSIZE( layout );
	if (!_shader.loadShaderFromFX("Shaders/aarows.fx", layout, numElements, true))
		return false;

	_cb.init(cb);

 //   D3D11_INPUT_ELEMENT_DESC layout2[] =
 //   {
 //       { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
 //       { "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
 //   };
	//numElements = ARRAYSIZE( layout2 );
	//_render.loadShaderFromFX("Shaders/pixel.fx", layout2, numElements);
	//
	//ID3D11DeviceContext * device = Devices::get()->getDeviceContext();
	//
	//
	//const UINT MaxVertices = 100;
	//D3D11_BUFFER_DESC bd;
	//bd.Usage = D3D11_USAGE_DEFAULT;
	//bd.ByteWidth = MaxVertices * sizeof(float) * 8;
	//bd.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
	//bd.CPUAccessFlags = 0;
	//bd.MiscFlags = 0;
	//
	//Devices::get()->getDevice11()->CreateBuffer( &bd, NULL, &m_pStreamTo );

 //   UINT offset[1] = { 0 };
 //   device->SOSetTargets( 1, &m_pStreamTo, offset );

 //   // Draw
	//_shader.applyWithGS();
	//_cb.applyGS(0);
	//_buffer.draw();
	//
 //   // Get back to normal
	//ID3D11Buffer* none = nullptr;
 //   device->SOSetTargets( 1, &none, offset );

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
	_shader.applyWithGS();
	_cb.applyGS(0);
	_buffer.draw();
	
	//ID3D11DeviceContext * device = Devices::get()->getDeviceContext();
 //   UINT stride[1] = { sizeof(float) * 7 };
 //   UINT offset[1] = { 0 };
 //   device->IASetPrimitiveTopology( D3D11_PRIMITIVE_TOPOLOGY_LINELIST );
 //   device->IASetVertexBuffers( 0, 1, &m_pStreamTo, stride, offset );
	//
	//_render.apply();
	//device->DrawAuto();
}
//--------------------------------------------------------------------