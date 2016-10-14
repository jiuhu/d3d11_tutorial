#pragma once

#include "Shape/Shape.h"
#include "D3D11/Texture/Texture.h"
#include "D3D11/Shader/Shader.h"
//--------------------------------------------------------------------

class Font
{
public:

	Font(const char * const fontName);

	void drawText(float x, float y, const char * const text);

private:

	Texture m_fontTexture;

	Shape m_fontShape;

	Shader m_fontShader;
};
//--------------------------------------------------------------------