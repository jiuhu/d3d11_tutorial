//--------------------------------------------------------------------
//
//	DxDevices.h
//
//	Ewe Yee Seong
//	MSc Games Programming, 2009 - 2010
//	University of Hull
//


/**	Revision History

		Rev 1.0		04 Nov 2011		Define DxDevices for D3D11

*/


#pragma once


#include <D3D11.h>
#include <d2d1.h>
#include <dwrite.h>
//--------------------------------------------------------------------

//--------------------------------------------------------------------

class DxDevices
{
public:

	/*
		Constructor.
	*/
	DxDevices();

	/*
		Destructor.
	*/
	~DxDevices();

	/*
		This function is called to initialize Direct3D 11 device.
	*/
	HRESULT init(HWND hWnd);

	/*
		This function is called to prepare for 2D rendering.
	*/
	void preDraw2D();

	/*
		This function is called to finalize 2D rendering.
	*/
	void postDraw2D();

	/*
		This function is called to prepare for 3D rendering.
	*/
	void preDraw3D();

	/*
		This function is called to finalize 3D rendering.
	*/
	void postDraw3D();

	/*
		This function is called to clear the screen.
	*/
	void clearScreen();

	/*
		This function is called to swap the buffer.
	*/
	void swap();

	/*
		This function is called to set the viewport.
	*/
	void setViewPort(FLOAT width, FLOAT height);
	
	/*
		This function is called to get the D3D11 device.
	*/
	ID3D11Device * getDevice11() const;

	/*
		This function is called to get the immediate context.
	*/
	ID3D11DeviceContext * getImmediateContext() const;
		
	/*
		This function is called to get the D2D1 render target.
	*/
	ID2D1RenderTarget * getD2DRenderTarget() const;
		
	/*
		This function is called to get the direct write factory.
	*/
	IDWriteFactory * getWriteFactory() const;
	
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

	//	Pointer to the D3D10.1 device.
	ID3D10Device1 * m_device10_1;

	//	Pointer to the shared texture buffer.
	ID3D11Texture2D * m_sharedTexture11;

	//	Pointer to the keyed mutex for D3D11.
	IDXGIKeyedMutex * m_keyedMutex11;

	//	Pointer to the keyed mutex for D3D10.1.
	IDXGIKeyedMutex * m_keyedMutex10;

	//	Pointer to the D2D1 render target.
	ID2D1RenderTarget * m_d2DRenderTarget;
	
	//	Pointer to the direct write factory.
	IDWriteFactory * m_writeFactory;
	
};
//--------------------------------------------------------------------

inline void safeRelease(IUnknown * pointer)
{
	if (pointer)
	{
		pointer->Release();
		pointer = nullptr;
	}
}
//--------------------------------------------------------------------

inline void DxDevices::setViewPort(FLOAT width, FLOAT height)
{
    D3D11_VIEWPORT vp;
    vp.Width = width;
    vp.Height = height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_immediateContext->RSSetViewports(1, &vp);
}
//--------------------------------------------------------------------

inline void DxDevices::clearScreen() 
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.6f, 1.0f };
	m_immediateContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
}
//----------------------------------------------------------------------------

inline void DxDevices::swap() 
{
	m_swapChain->Present(0, 0);
}
//----------------------------------------------------------------------------

inline void DxDevices::preDraw2D()
{			
	// Sync the shared texture for D3D10.1
	m_keyedMutex10->AcquireSync(0, INFINITE);	
	
	m_d2DRenderTarget->BeginDraw();
	
	m_d2DRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::SkyBlue));
	m_d2DRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
}
//--------------------------------------------------------------------

inline void DxDevices::postDraw2D()
{
	m_d2DRenderTarget->EndDraw();
	m_keyedMutex10->ReleaseSync(1);
}
//--------------------------------------------------------------------

inline void DxDevices::preDraw3D()
{
	// Sync the shared texture for D3D11
	m_keyedMutex11->AcquireSync(1, INFINITE);
			
	// Copy the content from the shared texture to the back-buffer
	m_immediateContext->CopyResource(m_backBuffer, m_sharedTexture11);
}
//--------------------------------------------------------------------

inline void DxDevices::postDraw3D()
{
	m_keyedMutex11->ReleaseSync(0);
	swap();
}
//--------------------------------------------------------------------

inline ID3D11Device * DxDevices::getDevice11() const
{
	return m_device11;
}
//--------------------------------------------------------------------
	
inline ID3D11DeviceContext * DxDevices::getImmediateContext() const
{
	return m_immediateContext;
}
//--------------------------------------------------------------------

inline ID2D1RenderTarget * DxDevices::getD2DRenderTarget() const
{
	return m_d2DRenderTarget;
}
//--------------------------------------------------------------------

inline IDWriteFactory * DxDevices::getWriteFactory() const
{
	return m_writeFactory;
}
//--------------------------------------------------------------------