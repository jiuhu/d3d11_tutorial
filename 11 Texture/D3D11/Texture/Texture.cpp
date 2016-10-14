#include "Texture.h"
#include "D3D11/DxDevices.h"
#include "WICTextureLoader.h"
#include "DDSTextureLoader.h"
#include "Utilities/Helper.h"
//--------------------------------------------------------------------

Texture::Texture()
	:	m_textureRV(nullptr)
{
	//	Empty
}
//--------------------------------------------------------------------

Texture::~Texture()
{
	safeRelease(m_textureRV);
}
//--------------------------------------------------------------------

bool Texture::loadTexture2DFromFile(LPCSTR textureFile)
{
	ID3D11Device * device = Devices::get()->getDevice11();
	
	//----------------------------------------
	//	Create WIC texture from file
	//----------------------------------------
	//ID3D11Resource * texture;
	HRESULT hr = CreateWICTextureFromFile(device, m_deviceContext, stringToWstring(textureFile).c_str(), nullptr, &m_textureRV);
	if(FAILED(hr))
	{
		printFormattedErrorMessage(hr, "CreateWICTextureFromFile for %s", textureFile); 
		return false;
	}

     
	//----------------------------------------
	//	Create the sample state
	//----------------------------------------
	//ID3D11SamplerState * m_samplerLinear;
 //   D3D11_SAMPLER_DESC sampDesc;
 //   ZeroMemory(&sampDesc, sizeof(sampDesc));
 //   sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
 //   sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
 //   sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
 //   sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
 //   sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
 //   sampDesc.MinLOD = 0;
 //   sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
 //   hr = device->CreateSamplerState( &sampDesc, &m_samplerLinear );
 //   if(FAILED(hr))
	//{
	//	printErrorMessage(hr, "CreateSamplerState"); 
 //       return false;
	//}

	//safeRelease(m_samplerLinear);

	return true;
}
//--------------------------------------------------------------------

bool Texture::loadTexture3DFromDDS(LPCSTR ddsFile)
{
	ID3D11Device * device = Devices::get()->getDevice11();
	
	//----------------------------------------
	//	Create DDS texture from file
	//----------------------------------------
	//ID3D11Resource * texture;
	HRESULT hr = DirectX::CreateDDSTextureFromFile(device, stringToWstring(ddsFile).c_str(), nullptr, &m_textureRV);
	if(FAILED(hr))
	{
		printFormattedErrorMessage(hr, "CreateWICTextureFromFile for %s", ddsFile); 
		return false;
	}
	
	//----------------------------------------
	//	Create the sample state
	//----------------------------------------
	ID3D11SamplerState * m_samplerLinear;
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));
    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = D3D11_FLOAT32_MAX;
    hr = device->CreateSamplerState( &sampDesc, &m_samplerLinear );
    if(FAILED(hr))
	{
		printErrorMessage(hr, "CreateSamplerState"); 
        return false;
	}
	//m_deviceContext->PSSetSamplers(
	safeRelease(m_samplerLinear);

	return true;
}
//--------------------------------------------------------------------