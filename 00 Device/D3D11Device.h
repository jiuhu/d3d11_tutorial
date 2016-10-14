//--------------------------------------------------------------------
//
//	D3D11Device.h
//
//	Ewe Yee Seong
//	MSc Games Programming, 2009 - 2010
//	University of Hull
//


/**	Revision History

		Rev 1.0		04 Nov 2011		Define D3D11Device for D3D11

*/


#pragma once

#include <D3D11.h>
//--------------------------------------------------------------------

#pragma comment (lib, "D3D11.lib")
//--------------------------------------------------------------------

class D3D11Device
{

public:

	/*
		Constructor.
	*/
	D3D11Device();

	/*
		Destructor.
	*/
	~D3D11Device();

	/*
		This function is called to initialize Direct3D 11 device.
	*/
	HRESULT init(HWND hWnd);

	/*
		This function is called to clear the screen.
	*/
	void clearScreen();

	/*
		This function is called to swap the buffer.
	*/
	void swap();
	
private:

	//	Pointer to the D3D11 device.
	ID3D11Device * m_device11;

	//	Pointer to the swap chain.
	IDXGISwapChain * m_swapChain;

	//	Pointer to the immediate context.
	ID3D11DeviceContext * m_immediateContext;

	//	Pointer to the back buffer.	
	ID3D11Texture2D * m_backBuffer;

	//	Pointer to the render target view.
	ID3D11RenderTargetView * m_renderTargetView;
	
};
//--------------------------------------------------------------------