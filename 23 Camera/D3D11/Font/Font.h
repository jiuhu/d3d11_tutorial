#pragma once

#include "D3D11/Texture/Texture.h"
#include "D3D11/Buffer/VertexBuffer.h"
#include "D3D11/Shader/Shader.h"
//--------------------------------------------------------------------

class Font
{
public:

	Font(const char * const fontName);

	void drawText(float x, float y, const char * const text);
	void drawFormattedText(float x, float y, const char * const format, ...);

private:

	Shader m_fontShader;

	VertexBuffer m_fontShape;

	Texture m_fontFace;
};
//--------------------------------------------------------------------