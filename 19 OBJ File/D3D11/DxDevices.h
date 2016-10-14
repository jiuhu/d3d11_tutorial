#pragma once

#include <D3D11.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include "Utilities/Singleton.h"
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
	bool init(HWND hWnd);

	/*
		This function is called to clear the screen.
	*/
	void clear();

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
	ID3D11DeviceContext * getDeviceContext() const;

	/*
		This function is called to create a blending state.
	*/
	void createBlendState(D3D11_BLEND src = D3D11_BLEND_SRC_ALPHA, D3D11_BLEND dest = D3D11_BLEND_INV_SRC_ALPHA);

	/*
		This function is called to enable blending.
	*/
	void enableBlend() const;

	/*
		This function is called to disable blending.
	*/
	void disableBlend() const;

	/*
		This function is called to change cull mode.
	*/
	void cullMode(D3D11_CULL_MODE mode) const;

	/*
		This function is called to change polygon mode.
	*/
	void polygonMode(D3D11_FILL_MODE mode) const;

	/*
		This function is called to enable depth test.
	*/
	void enableDepth() const;

	/*
		This function is called to disable depth test.
	*/
	void disableDepth() const;

	/*
		This function is called to toggle depth test.
	*/
	void toggleDepth(bool depthOn) const;
	
private:

	//	Pointer to the D3D11 device.
	ID3D11Device * m_device11;

	//	Pointer to the swap chain.
	IDXGISwapChain * m_swapChain;

	//	Pointer to the immediate context.
	ID3D11DeviceContext * m_deviceContext;

	//	Pointer to the back buffer.	
	ID3D11Texture2D * m_backBuffer;

	//	Pointer to the render target view.
	ID3D11RenderTargetView * m_renderTargetView;

	//	Pointer to the depth stencil view.
	ID3D11DepthStencilView * m_depthStencilView;

	//	Pointer to the blend state.	
	ID3D11BlendState * m_blendState;
};
//--------------------------------------------------------------------

//	Define a global for input device.
typedef Singleton<DxDevices> Devices;
//--------------------------------------------------------------------

void printErrorMessage(HRESULT hr, const char * const message);
//--------------------------------------------------------------------

void printFormattedErrorMessage(HRESULT hr, const char * const format, ...);
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
    m_deviceContext->RSSetViewports(1, &vp);
}
//--------------------------------------------------------------------

inline void DxDevices::clear() 
{
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	m_deviceContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
    m_deviceContext->ClearDepthStencilView(m_depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}
//----------------------------------------------------------------------------

inline void DxDevices::swap() 
{
	m_swapChain->Present(0, 0);
}
//----------------------------------------------------------------------------

inline ID3D11Device * DxDevices::getDevice11() const
{
	return m_device11;
}
//----------------------------------------------------------------------------
	
inline ID3D11DeviceContext * DxDevices::getDeviceContext() const
{
	return m_deviceContext;
}
//----------------------------------------------------------------------------

inline void DxDevices::enableDepth() const
{
	toggleDepth(true);
}
//----------------------------------------------------------------------------

inline void DxDevices::disableDepth() const
{
	toggleDepth(false);
}
//----------------------------------------------------------------------------

inline void DxDevices::enableBlend() const
{
	//float blendFactor[] = {0.75f, 0.75f, 0.75f, 1.0f};
	m_deviceContext->OMSetBlendState(m_blendState, 0, 0xffffffff);
}
//----------------------------------------------------------------------------

inline void DxDevices::disableBlend() const
{
	m_deviceContext->OMSetBlendState(0, 0, 0xffffffff);
}
//----------------------------------------------------------------------------