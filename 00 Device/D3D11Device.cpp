//--------------------------------------------------------------------
//
//	D3D11Device.cpp
//
//	Ewe Yee Seong
//	MSc Games Programming, 2009 - 2010
//	University of Hull
//


#include "D3D11Device.h"
//--------------------------------------------------------------------

D3D11Device::D3D11Device()
	:	m_device11(nullptr),
		m_swapChain(nullptr),
		m_immediateContext(nullptr),
		m_backBuffer(nullptr),
		m_renderTargetView(nullptr)
		
{
	//	Empty
}
//--------------------------------------------------------------------

D3D11Device::~D3D11Device()
{
	m_renderTargetView->Release();

	m_swapChain->SetFullscreenState(FALSE, NULL);
	
	m_immediateContext->ClearState();
	m_backBuffer->Release();
	
	m_immediateContext->Flush();
	
	m_immediateContext->Release();
	m_swapChain->Release();
	m_device11->Release();
}
//--------------------------------------------------------------------

HRESULT D3D11Device::init(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;

	//--------------------------------
	//	Initialize for D3D11
	//--------------------------------

	DXGI_SWAP_CHAIN_DESC sd;	
	ZeroMemory(&sd, sizeof(sd));
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;
	
	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_10_1;
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		&level,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&m_swapChain,
		&m_device11,
		NULL,
		&m_immediateContext
	);
	if(FAILED(hr))
		return hr;

	// Get the D3D11 back-buffer
	D3D11_TEXTURE2D_DESC backBufferDesc;	
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer));
	if(FAILED(hr))
		return hr;
	
	m_backBuffer->GetDesc(&backBufferDesc);

	
    hr = m_device11->CreateRenderTargetView(m_backBuffer, NULL, &m_renderTargetView);
	if(FAILED(hr))
		return hr;

    m_immediateContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);

    // Setup the viewport
    D3D11_VIEWPORT vp;
    vp.Width = (FLOAT)width;
    vp.Height = (FLOAT)height;
    vp.MinDepth = 0.0f;
    vp.MaxDepth = 1.0f;
    vp.TopLeftX = 0;
    vp.TopLeftY = 0;
    m_immediateContext->RSSetViewports(1, &vp);

	return hr;
}
//--------------------------------------------------------------------

void D3D11Device::clearScreen() 
{
	float ClearColor[4] = { 0.0f, 0.125f, 0.6f, 1.0f };
	m_immediateContext->ClearRenderTargetView(m_renderTargetView, ClearColor);
}
//--------------------------------------------------------------------

void D3D11Device::swap() 
{
	m_swapChain->Present(0, 0);
}
//--------------------------------------------------------------------