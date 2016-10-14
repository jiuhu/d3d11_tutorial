#include "BigBox.h"
#include "D3D11/DxDevices.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

bool BigBox::init(LPCSTR textureFile, float size)
{	
	if (!m_texture.loadTexture2DFromFile(textureFile)) return false;

	m_box.generateCube(size, true, true);

	m_world.identity();
	
	return true;
}
//--------------------------------------------------------------------

void BigBox::draw(DxDevices * devices)
{
	m_texture.apply(0);

	devices->cullMode(D3D11_CULL_FRONT);
	m_box.draw();

	devices->enableBlend();
	devices->cullMode(D3D11_CULL_BACK);
	m_box.draw();
	devices->disableBlend();
}
//--------------------------------------------------------------------