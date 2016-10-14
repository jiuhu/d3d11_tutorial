#include "Shader.h"
#include "D3D11/DxDevices.h"
#include <d3dcompiler.h>
#include "Utilities/Debug.h"
#include "Utilities/Helper.h"
//--------------------------------------------------------------------

#pragma comment (lib, "D3dcompiler.lib")
//--------------------------------------------------------------------

#if (_WIN32_WINNT == _WIN32_WINNT_WIN7)
	#include <D3DX11.h>
	#pragma comment (lib, "d3dx11.lib")
#endif
//--------------------------------------------------------------------

Shader::Shader()
	:	m_vertexShader(nullptr),
		m_pixelShader(nullptr),
		m_geometryShader(nullptr),
		m_inputLayout(nullptr)
{
	//	Empty
}
//--------------------------------------------------------------------

Shader::~Shader()
{
	safeRelease(m_inputLayout);

	safeRelease(m_geometryShader);

	safeRelease(m_pixelShader);

	safeRelease(m_vertexShader);
}
//--------------------------------------------------------------------

bool Shader::loadShaderFromFX(LPCSTR fxFile, const D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements)
{
	ID3D11Device * device = Devices::get()->getDevice11();
	
	//----------------------------------------
	//	Compile the vertex shader
	//----------------------------------------
    ID3DBlob * vsBlob = nullptr;    
	HRESULT hr = compileShaderFromFX(fxFile, "vs_main", "vs_4_0", &vsBlob);
    if(FAILED(hr)) return false;
	
	
	//----------------------------------------
	//	Create the input layout
	//----------------------------------------
	hr = device->CreateInputLayout(layout, numElements, vsBlob->GetBufferPointer(), vsBlob->GetBufferSize(), &m_inputLayout);
	vsBlob->Release();
	if(FAILED(hr))
	{
		printErrorMessage(hr, "CreateInputLayout");
		safeRelease(m_inputLayout);
        return false;
	}
	
	//----------------------------------------
	//	Compile the pixel shader
	//----------------------------------------
	hr = compileShaderFromFX(fxFile, "ps_main", "ps_4_0");
    if(FAILED(hr)) return false;


	return true;
}
//--------------------------------------------------------------------

bool Shader::loadGeometryShaderFromFX(LPCSTR fxFile, const D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements)
{
	if (!loadShaderFromFX(fxFile, layout, numElements))
		return false;

	//----------------------------------------
	//	Compile the geometry shader
	//----------------------------------------
    HRESULT hr = compileShaderFromFX(fxFile, "gs_main", "gs_4_0");
    if(FAILED(hr)) return false;

	return true;
}
//--------------------------------------------------------------------

HRESULT Shader::compileShaderFromFX(LPCSTR fxFile, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob ** blob)
{	
    UINT flags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
    flags |= D3DCOMPILE_DEBUG;
#endif

    ID3DBlob * outputMessageBlob = nullptr;
    ID3DBlob * shaderBlob = nullptr;
	
	#if (_WIN32_WINNT == _WIN32_WINNT_WIN7)
		HRESULT hr = D3DX11CompileFromFile(fxFile, NULL, NULL, entryPoint, shaderModel, flags, 0, NULL, &blob, &outputMessageBlob, NULL );
	#else
		HRESULT hr = D3DCompileFromFile(stringToWstring(fxFile).c_str(), NULL, NULL, entryPoint, shaderModel, flags, 0, &shaderBlob, &outputMessageBlob);
	#endif
	
    if (outputMessageBlob)
    {
        outputMsg((char*)outputMessageBlob->GetBufferPointer());
        safeRelease(outputMessageBlob);
    }

    if (FAILED(hr))
    {
		printFormattedErrorMessage(hr, "compileShaderFromFX for %s", fxFile);
		safeRelease(shaderBlob);        
		return hr;
    }
	
	if (shaderBlob)
	{
		ID3D11Device * device = Devices::get()->getDevice11();
		std::string message;
		if (strstr( shaderModel, "vs"))
		{
			hr = device->CreateVertexShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), NULL, &m_vertexShader);
			message = "CreateVertexShader";
		}
		else if (strstr( shaderModel, "ps"))
		{
			hr = device->CreatePixelShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), NULL, &m_pixelShader);
			message = "CreatePixelShader";
		}
		else if (strstr( shaderModel, "gs"))
		{
			hr = device->CreateGeometryShader(shaderBlob->GetBufferPointer(), shaderBlob->GetBufferSize(), NULL, &m_geometryShader);
			message = "CreateGeometryShader";
		}

		if(FAILED(hr))
		{
			printErrorMessage(hr, message.c_str());
			shaderBlob->Release();
			return false;
		}

		if (blob)
		{
			*blob = shaderBlob;
		}
		else
		{
			shaderBlob->Release();
		}
	}

	return hr;
}
//--------------------------------------------------------------------