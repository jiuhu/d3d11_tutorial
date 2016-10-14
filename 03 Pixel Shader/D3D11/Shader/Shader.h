#pragma once

#include "D3D11/IRender.h"
//--------------------------------------------------------------------

class Shader : public IRender
{
public:

	/*
		Constructor.
	*/
	Shader();

	/*
		Destructor.
	*/
	~Shader();

	/*
		This function is called to apply the shader effect.
	*/
	void apply();

	/*
		This function is called to apply the shader effect with geometry shader.
	*/
	void applyWithGS();
	
	/*
		This function is called to setup shaders and link to program.
	*/
	bool loadShaderFromFX(LPCSTR fxFile, const D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements);
	
	/*
		This function is called to setup shaders and link to program.
	*/
	bool loadGeometryShaderFromFX(LPCSTR fxFile, const D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements);

private:
	
	//	Pointer to the vertex shader.
	ID3D11VertexShader * m_vertexShader;

	//	Pointer to the pixel shader.
	ID3D11PixelShader * m_pixelShader;

	//	Pointer to the geometry shader.
	ID3D11GeometryShader * m_geometryShader;

	//	Pointer to the input layout.
	ID3D11InputLayout * m_inputLayout;

	/*
		This function is called to compile a shader from file.
	*/
	HRESULT compileShaderFromFX(LPCSTR fxFile, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob ** blob = nullptr);
};
//--------------------------------------------------------------------

inline void Shader::apply() 
{
    // Set the input layout
	if (m_deviceContext) 
	{
		m_deviceContext->IASetInputLayout(m_inputLayout);
		if (m_vertexShader) m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
		if (m_pixelShader) m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	}
}
//--------------------------------------------------------------------

inline void Shader::applyWithGS() 
{
    // Set the input layout
	if (m_deviceContext) 
	{
		m_deviceContext->IASetInputLayout(m_inputLayout);
		if (m_vertexShader) m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
		if (m_geometryShader) m_deviceContext->GSSetShader(m_geometryShader, NULL, 0);
		if (m_pixelShader) m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	}
}
//--------------------------------------------------------------------