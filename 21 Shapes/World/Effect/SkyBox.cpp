#include "SkyBox.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

bool SkyBox::init(LPCSTR textureFile, float size)
{	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	if (!m_shader.loadShaderFromFX("Shaders/skybox.fx", layout, ARRAYSIZE(layout))) return false;
	
	if (!m_texture.loadTextureFromDDS(textureFile)) return false;

	m_box.generateCubeVertexOnly(size);
	
	return true;
}
//--------------------------------------------------------------------

void SkyBox::draw()
{
	m_shader.apply();

	m_texture.apply(0);


	Devices::get()->cullMode(D3D11_CULL_FRONT);
	m_box.draw();
	Devices::get()->cullMode(D3D11_CULL_BACK);
}
//--------------------------------------------------------------------