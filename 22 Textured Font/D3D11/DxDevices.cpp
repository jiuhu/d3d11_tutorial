#include "DxDevices.h"
#include "IRender.h"
#include "Utilities/Debug.h"
//----------------------------------------------------------------------------

#pragma comment (lib, "D3D11.lib")
#pragma comment (lib, "Windowscodecs.lib")
//----------------------------------------------------------------------------

DxPositioner DxDevices::_positioner;
//----------------------------------------------------------------------------

DxDevices::DxDevices()
	:	m_device11(nullptr),
		m_swapChain(nullptr),
		m_deviceContext(nullptr),
		m_backBuffer(nullptr),
		m_renderTargetView(nullptr),
		m_depthStencilView(nullptr),
		m_blendState(nullptr)
{
	//	Empty
}
//----------------------------------------------------------------------------

DxDevices::~DxDevices()
{
	safeRelease(m_blendState);

	safeRelease(m_depthStencilView);
	safeRelease(m_renderTargetView);

	m_swapChain->SetFullscreenState(FALSE, NULL);	
	m_deviceContext->ClearState();

	safeRelease(m_backBuffer);
	
	m_deviceContext->Flush();
	
	safeRelease(m_deviceContext);
	safeRelease(m_swapChain);
	safeRelease(m_device11);
}
//----------------------------------------------------------------------------

bool DxDevices::init(HWND hWnd)
{
	RECT rc;
	GetClientRect(hWnd, &rc);

	int width = rc.right - rc.left,
		height = rc.bottom - rc.top;

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
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = TRUE;
	
	D3D_FEATURE_LEVEL level;
	D3D_FEATURE_LEVEL levels[] = {	
									D3D_FEATURE_LEVEL_11_0,
									D3D_FEATURE_LEVEL_10_1,
									D3D_FEATURE_LEVEL_10_0,
									D3D_FEATURE_LEVEL_9_3,
									D3D_FEATURE_LEVEL_9_2,
									D3D_FEATURE_LEVEL_9_1
								};
	
	HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, levels, ARRAYSIZE(levels), 
												D3D11_SDK_VERSION, &sd, &m_swapChain, &m_device11, &level, &m_deviceContext);
	
	if(FAILED(hr))
	{
		printErrorMessage(hr, "D3D11CreateDeviceAndSwapChain"); 
        return false;
	}

	IRender::setDeviceContext(m_deviceContext);
	

	//----------------------------------------
	//	Initialize for Render Target View
	//----------------------------------------
	D3D11_TEXTURE2D_DESC backBufferDesc;	
	hr = m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&m_backBuffer));
	if(FAILED(hr))
	{
		printErrorMessage(hr, "GetBuffer"); 
        return false;
	}	
	m_backBuffer->GetDesc(&backBufferDesc);

    hr = m_device11->CreateRenderTargetView(m_backBuffer, NULL, &m_renderTargetView);
	if(FAILED(hr))
	{
		printErrorMessage(hr, "CreateRenderTargetView"); 
        return false;
	}

    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, NULL);


	//----------------------------------------
	//	Initialize for Depth Stencil Buffer
	//----------------------------------------
    D3D11_TEXTURE2D_DESC descDepth;
    ZeroMemory(&descDepth, sizeof(descDepth));
    descDepth.Width = width;
    descDepth.Height = height;
    descDepth.MipLevels = 1;
    descDepth.ArraySize = 1;
    descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    descDepth.SampleDesc.Count = 1;
    descDepth.Usage = D3D11_USAGE_DEFAULT;
    descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	
	ID3D11Texture2D * depthStencil;
    hr = m_device11->CreateTexture2D(&descDepth, NULL, &depthStencil);
    if(FAILED(hr))
	{
		printErrorMessage(hr, "CreateTexture2D"); 
        return false;
	}

    D3D11_DEPTH_STENCIL_VIEW_DESC descDSV;
    ZeroMemory(&descDSV, sizeof(descDSV));
    descDSV.Format = descDepth.Format;
    descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;

    hr = m_device11->CreateDepthStencilView(depthStencil, &descDSV, &m_depthStencilView);
	safeRelease(depthStencil);
	if(FAILED(hr))
	{
		printErrorMessage(hr, "CreateDepthStencilView"); 
        return false;
	}
	
    m_deviceContext->OMSetRenderTargets(1, &m_renderTargetView, m_depthStencilView);	
	
	D3D11_DEPTH_STENCIL_DESC dsd;
	dsd.DepthEnable = true;
	dsd.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsd.DepthFunc = D3D11_COMPARISON_LESS;
	dsd.StencilEnable = true;
	dsd.StencilReadMask = 0xFF;
	dsd.StencilWriteMask = 0xFF;
	dsd.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	dsd.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
	dsd.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	dsd.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	dsd.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	// Create depth stencil state
	ID3D11DepthStencilState * depthStencilState;
	m_device11->CreateDepthStencilState(&dsd, &depthStencilState);
	m_deviceContext->OMSetDepthStencilState(depthStencilState, 1);
	

	//----------------------------------------
	//	Initialize for Rasterizer state
	//----------------------------------------	
	D3D11_RASTERIZER_DESC rd;
    ZeroMemory(&rd, sizeof(rd));
	rd.CullMode = D3D11_CULL_BACK;
	rd.DepthClipEnable = true;
	rd.FillMode = D3D11_FILL_SOLID;
	
	ID3D11RasterizerState * rasterizerState;
	m_device11->CreateRasterizerState(&rd, &rasterizerState);
	m_deviceContext->RSSetState(rasterizerState);
	safeRelease(rasterizerState);


	//----------------------------------------
	//	Initialize for Blend state
	//----------------------------------------	
	createBlendState();

	//----------------------------------------
	//	Initialize for ViewPort
	//----------------------------------------
	setViewPort((FLOAT)width, (FLOAT)height);
	
	_positioner.init();

	//----------------------------------------
	//	End of Initialization
	//----------------------------------------

	return true;
}
//----------------------------------------------------------------------------

void printErrorMessage(HRESULT hr, const char * const message)
{
	LPVOID lpMsgBuf;
	FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL, hr, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);

	outputMsg("%s failed : %s", message, lpMsgBuf);
}
//----------------------------------------------------------------------------

void printFormattedErrorMessage(HRESULT hr, const char * const format, ...)
{
	va_list args;
	va_start(args, format);
	int size = _vscprintf(format, args) + 1;
	char * strBuffer = new char[size];
	vsprintf_s(strBuffer, size, format, args);
	va_end(args);
	
	printErrorMessage(hr, strBuffer);
	delete [] strBuffer;
}
//----------------------------------------------------------------------------

void DxDevices::createBlendState(D3D11_BLEND src, D3D11_BLEND dest)
{
	D3D11_BLEND_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.RenderTarget[0].BlendEnable = TRUE;
	bd.RenderTarget[0].SrcBlend = src;
	bd.RenderTarget[0].DestBlend = dest;
	bd.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	bd.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	bd.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;//0x0f;
	
	safeRelease(m_blendState);
	m_device11->CreateBlendState(&bd, &m_blendState);
}
//----------------------------------------------------------------------------

void DxDevices::cullMode(D3D11_CULL_MODE mode) const
{
	ID3D11RasterizerState * rasterizerState;
	m_deviceContext->RSGetState(&rasterizerState);
	
	D3D11_RASTERIZER_DESC rd;
	rasterizerState->GetDesc(&rd);
	rd.CullMode = mode;
	
	m_device11->CreateRasterizerState(&rd, &rasterizerState);
	m_deviceContext->RSSetState(rasterizerState);
	safeRelease(rasterizerState);
}
//----------------------------------------------------------------------------

void DxDevices::polygonMode(D3D11_FILL_MODE mode) const
{
	ID3D11RasterizerState * rasterizerState;
	m_deviceContext->RSGetState(&rasterizerState);
	
	D3D11_RASTERIZER_DESC rd;
	rasterizerState->GetDesc(&rd);
	rd.FillMode = mode;
	
	m_device11->CreateRasterizerState(&rd, &rasterizerState);
	m_deviceContext->RSSetState(rasterizerState);
	safeRelease(rasterizerState);
}
//----------------------------------------------------------------------------

void DxDevices::toggleDepth(bool depthOn) const
{
	ID3D11DepthStencilState * depthStencilState;
	UINT ref;
	m_deviceContext->OMGetDepthStencilState(&depthStencilState, &ref);
	
	D3D11_DEPTH_STENCIL_DESC dsd;
	depthStencilState->GetDesc(&dsd);
	dsd.DepthEnable = depthOn;

	m_device11->CreateDepthStencilState(&dsd, &depthStencilState);
	m_deviceContext->OMSetDepthStencilState(depthStencilState, ref);
}
//----------------------------------------------------------------------------