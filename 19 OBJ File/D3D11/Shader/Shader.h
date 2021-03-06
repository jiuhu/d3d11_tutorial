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
		This function is called to setup shaders and link to program.
	*/
	bool loadShaderFromFX(LPCSTR fxFile, const D3D11_INPUT_ELEMENT_DESC layout[], UINT numElements, bool hasGS = false);

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

	/*
		This function is called to compile a shader from file.
	*/
	HRESULT compileShaderFromMemory(LPCVOID srcData, size_t size, LPCSTR entryPoint, LPCSTR shaderModel, ID3DBlob ** blob = nullptr);
};
//--------------------------------------------------------------------

inline void Shader::apply() 
{
    // Set the input layout
	if (m_deviceContext) 
	{
		m_deviceContext->IASetInputLayout(m_inputLayout);
		m_deviceContext->VSSetShader(m_vertexShader, NULL, 0);
		m_deviceContext->GSSetShader(m_geometryShader, NULL, 0);
		m_deviceContext->PSSetShader(m_pixelShader, NULL, 0);
	}
}
//--------------------------------------------------------------------