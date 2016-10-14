#pragma once

#ifndef __d3d11_h__
	#include <D3D11.h>
#endif
//--------------------------------------------------------------------

class IRender
{
public:
	
	/*
		This function is called to set the device context.
	*/
	static void setDeviceContext(ID3D11DeviceContext * context);

protected:

	//	Pointer to the immediate context.
	static ID3D11DeviceContext * m_deviceContext;
};
//--------------------------------------------------------------------

inline void IRender::setDeviceContext(ID3D11DeviceContext * context)
{
	m_deviceContext = context;
}
//--------------------------------------------------------------------