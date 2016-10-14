#pragma once

#include "D3D11/IRender.h"
//--------------------------------------------------------------------

class Texture : public IRender
{

public:

	/*
		Constructor.
	*/
	Texture();

	/*
		Destructor.
	*/
	~Texture();

	/*
		This function is called to apply the texture effect.
	*/
	void apply(UINT startSlot);
	
	/*
		This function is called to setup texture 2D and link to program.
	*/
	bool loadTexture2DFromFile(LPCSTR textureFile);
	
	/*
		This function is called to setup texture 3D and link to program.
	*/
	bool loadTexture3DFromDDS(LPCSTR ddsFile);

private:

	//	Pointer to the texture resource.
	ID3D11ShaderResourceView * m_textureRV;
};
//--------------------------------------------------------------------

inline void Texture::apply(UINT startSlot) 
{
    m_deviceContext->PSSetShaderResources(startSlot, 1, &m_textureRV);
    //m_deviceContext->PSSetSamplers( 0, 1, &m_samplerLinear );
}
//--------------------------------------------------------------------