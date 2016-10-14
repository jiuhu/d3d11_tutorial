//----------------------------------------------------------------------------
//
//	DxDevices.cpp
//
//	Ewe Yee Seong
//	MSc Games Programming, 2009 - 2010
//	University of Hull
//


#include "DxDevices.h"
//----------------------------------------------------------------------------

#pragma comment (lib, "D3D11.lib")
#pragma comment (lib, "DXGI.lib")
#pragma comment (lib, "D3D10_1.lib")
#pragma comment (lib, "D2D1.lib")
#pragma comment (lib, "dwrite.lib")
//----------------------------------------------------------------------------

DxDevices::DxDevices()
	:	m_device11(nullptr),
		m_swapChain(nullptr),
		m_immediateContext(nullptr),
		m_backBuffer(nullptr),
		m_renderTargetView(nullptr),
		m_device10_1(nullptr),
		m_sharedTexture11(nullptr),
		m_keyedMutex11(nullptr),
		m_keyedMutex10(nullptr),
		m_d2DRenderTarget(nullptr),
		m_writeFactory(nullptr)
{
	//	Empty
}
//----------------------------------------------------------------------------

DxDevices::~DxDevices()
{
	safeRelease(m_writeFactory);
	safeRelease(m_d2DRenderTarget);

	safeRelease(m_keyedMutex10);
	safeRelease(m_keyedMutex11);

	safeRelease(m_sharedTexture11);
	safeRelease(m_device10_1);

	safeRelease(m_renderTargetView);

	m_swapChain->SetFullscreenState(FALSE, NULL);	
	m_immediateContext->ClearState();

	safeRelease(m_backBuffer);
	
	m_immediateContext->Flush();
	
	safeRelease(m_immediateContext);
	safeRelease(m_swapChain);
	safeRelease(m_device11);
}
//----------------------------------------------------------------------------

HRESULT DxDevices::init(HWND hWnd)
{
	//----------------------------------------
	//	Get client information
	//----------------------------------------
	RECT rc;
	GetClientRect(hWnd, &rc);
	UINT width = rc.right - rc.left;
	UINT height = rc.bottom - rc.top;


	//----------------------------------------
	//	Initialize for DXGI
	//----------------------------------------	
	// Create DXGI factory to enumerate adapters
	IDXGIFactory1 * dXGIFactory;
	
	HRESULT hr = CreateDXGIFactory1(__uuidof(IDXGIFactory1), (void**)&dXGIFactory);
	if(FAILED(hr))
		return hr;
	
	// Use the first adapter
	IDXGIAdapter1 * adapter;
	
	hr = dXGIFactory->EnumAdapters1(0, &adapter);
	if(FAILED(hr))
		return hr;
	
	safeRelease(dXGIFactory);


	//----------------------------------------
	//	Initialize for D3D11
	//----------------------------------------

	DXGI_SWAP_CHAIN_DESC sd;	
	ZeroMemory(&sd, sizeof(sd));
    sd.BufferDesc.Width = width;
    sd.BufferDesc.Height = height;
    sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    sd.BufferDesc.RefreshRate.Numerator = 60;
    sd.BufferDesc.RefreshRate.Denominator = 1;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;
	
	UINT flags = D3D11_CREATE_DEVICE_DEBUG | D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_SINGLETHREADED;
	D3D_FEATURE_LEVEL level = D3D_FEATURE_LEVEL_10_1;
	hr = D3D11CreateDeviceAndSwapChain(adapter, D3D_DRIVER_TYPE_UNKNOWN, NULL, flags, &level, 1,
								D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device11, NULL, &m_immediateContext);
	
	if(FAILED(hr))
		return hr;

	// Get the D3D11 back-buffer
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer));
	if(FAILED(hr))
		return hr;
	
	D3D11_TEXTURE2D_DESC backBufferDesc;	
	m_backBuffer->GetDesc(&backBufferDesc);
	
	//	Create the render target view
    hr = m_device11->CreateRenderTargetView(m_backBuffer, NULL, &m_renderTargetView);
	m_backBuffer->Release();
	if(FAILED(hr))
		return hr;

    m_immediateContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);

    // Setup the viewport
	setViewPort((FLOAT)width, (FLOAT)height);
	
	
	//----------------------------------------
	//	Initialize for D3D10.1
	//----------------------------------------
		
	flags = D3D10_CREATE_DEVICE_DEBUG | D3D10_CREATE_DEVICE_BGRA_SUPPORT | D3D10_CREATE_DEVICE_SINGLETHREADED;
	hr = D3D10CreateDevice1(adapter, D3D10_DRIVER_TYPE_HARDWARE, NULL, flags,
		D3D10_FEATURE_LEVEL_10_1, D3D10_1_SDK_VERSION, &m_device10_1);
	if(FAILED(hr))
		return hr;

	
	safeRelease(adapter);
	
	// Create the shared texture to draw D2D content to
	D3D11_TEXTURE2D_DESC sharedTextureDesc;
	ZeroMemory(&sharedTextureDesc, sizeof(sharedTextureDesc));
	sharedTextureDesc.Width = backBufferDesc.Width;
	sharedTextureDesc.Height = backBufferDesc.Height;
	sharedTextureDesc.MipLevels = 1;
	sharedTextureDesc.ArraySize = 1;
	sharedTextureDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sharedTextureDesc.SampleDesc.Count = 1;
	sharedTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	sharedTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	sharedTextureDesc.MiscFlags = D3D11_RESOURCE_MISC_SHARED_KEYEDMUTEX;
	
	hr = m_device11->CreateTexture2D(&sharedTextureDesc, NULL, &m_sharedTexture11);
	if(FAILED(hr))
		return hr;


	//----------------------------------------
	//	Initialize for D2D1
	//----------------------------------------
	
	// Create D2D factory
	ID2D1Factory * d2DFactory;
	
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), (void**)&d2DFactory);
	if (FAILED(hr))
		return false;
	
	// Create D2D render target from the surface for the shared texture, which was opened in D3D10.1
	D2D1_RENDER_TARGET_PROPERTIES renderTargetProperties;
	ZeroMemory(&renderTargetProperties, sizeof(renderTargetProperties));
	renderTargetProperties.type = D2D1_RENDER_TARGET_TYPE_HARDWARE;
	renderTargetProperties.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED);
	
	
	//----------------------------------------
	//	Initialize for shared resources
	//----------------------------------------
	
	// Get the keyed mutex for the shared texture (for D3D11)	
	hr = m_sharedTexture11->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&m_keyedMutex11);
	if(FAILED(hr))
		return hr;
	
	// Get the shared handle needed to open the shared texture in D3D10.1
	IDXGIResource * sharedResource11;	
	hr = m_sharedTexture11->QueryInterface(__uuidof(IDXGIResource), (void**)&sharedResource11);
	if(FAILED(hr))
		return hr;
	
	HANDLE hSharedHandle11;
	sharedResource11->GetSharedHandle(&hSharedHandle11);
	if(FAILED(hr))
		return hr;
	
	safeRelease(sharedResource11);
	
	// Open the surface for the shared texture in D3D10.1
	IDXGISurface1 * sharedSurface10;	
	hr = m_device10_1->OpenSharedResource(hSharedHandle11, __uuidof(IDXGISurface1), (void**)(&sharedSurface10));
	if(FAILED(hr))
		return hr;
	
	// Get the keyed mutex for the shared texture for D3D10.1
	hr = sharedSurface10->QueryInterface(__uuidof(IDXGIKeyedMutex), (void**)&m_keyedMutex10);
	if(FAILED(hr))
		return hr;
	
	//	Create surface render target for D2D render target
	hr = d2DFactory->CreateDxgiSurfaceRenderTarget(sharedSurface10, &renderTargetProperties, &m_d2DRenderTarget);
	if (FAILED(hr))
		return hr;
	
	safeRelease(sharedSurface10);
	safeRelease(d2DFactory);
	

	//----------------------------------------
	//	Initialize for DirectWrite
	//----------------------------------------

	hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&m_writeFactory)
			);
	if (FAILED(hr))
		return false;
	

	//----------------------------------------
	//	End of Initialization
	//----------------------------------------

	return hr;
}
//----------------------------------------------------------------------------