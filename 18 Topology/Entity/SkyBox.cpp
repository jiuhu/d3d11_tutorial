#include "SkyBox.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

	float time[] = {4.0f, 0.0f, 0.0f, 0.0f };
bool SkyBox::init(LPCSTR textureFile, float size)
{	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	if (!m_shader.loadShaderFromFX("Shaders/cloud.fx", layout, ARRAYSIZE(layout))) return false;
	
	if (!m_texture.loadTextureFromDDS(textureFile)) return false;
	if (!m_texture2.loadTextureFromDDS("Texture/NoiseVolume.dds")) return false;

	m_box.generateCubeVertexOnly(size);

	_time.init(time);

	return true;
}
//--------------------------------------------------------------------

void SkyBox::draw(const ConstantBuffer &cameraBuffer)
{
	m_shader.apply();

	cameraBuffer.applyVS(0);

	m_texture.apply(0);
	m_texture2.apply(1);

	if (time[0] > 100.0f) time[0] = 0.0f;
	time[0] += 0.0167f;
	_time.updateData(time);
	_time.applyPS(1);

	Devices::get()->cullMode(D3D11_CULL_FRONT);
	m_box.draw();
	Devices::get()->cullMode(D3D11_CULL_BACK);
}
//--------------------------------------------------------------------