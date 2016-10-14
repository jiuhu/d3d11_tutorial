#include "ConstantBuffer.h"
#include "D3D11/DxDevices.h"
//--------------------------------------------------------------------

ConstantBuffer::ConstantBuffer()
	:	m_constantBuffer(nullptr)
{
    //	Empty
}
//--------------------------------------------------------------------

ConstantBuffer::~ConstantBuffer()
{
	safeRelease(m_constantBuffer);
}
//--------------------------------------------------------------------

bool ConstantBuffer::init(const void * data, int size, const char * const name)
{
	//----------------------------------------
	//	Create Constant Buffer
	//----------------------------------------
    D3D11_BUFFER_DESC bd;
    ZeroMemory(&bd, sizeof(bd));
    bd.Usage = D3D11_USAGE_DEFAULT;
    bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.ByteWidth = size;

    HRESULT hr = Devices::get()->getDevice11()->CreateBuffer(&bd, NULL, &m_constantBuffer);
	if (FAILED(hr))
	{
		printFormattedErrorMessage(hr, "CreateBuffer for %s", name);
        return false;
	}
    
	updateData(data);
	return true;
}
//--------------------------------------------------------------------