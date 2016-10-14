#include "Font.h"
#include "Shape/Shapes.h"
#include <vector>
#include <string>
//--------------------------------------------------------------------

const float fontWidth = 16.0f,
			fontHeight = 32.0f,
			uStep = fontWidth / 256.0f, 
			vStep = fontHeight / 256.0f;
//--------------------------------------------------------------------

Font::Font(const char * const fontName)
{	
    D3D11_INPUT_ELEMENT_DESC layout[] =
    {
        { "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
        { "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0 },
    };
	m_fontShader.loadShaderFromFX("Shaders/font.fx", layout, ARRAYSIZE(layout));

	std::string fontFileName = "Font/";
	fontFileName.append(fontName).append(".bmp");
	m_fontTexture.loadTexture2DFromFile(fontFileName.c_str());	
	m_fontTexture.apply(0);
}
//--------------------------------------------------------------------

void Font::drawText(float x, float y, const char * const text)
{
	//	First calculate the message size
	int size = strlen(text);

	std::vector<VertexFont> vertices;
	float xi = x, yi = y;
	for (int i = 0; i < size; ++i)
	{
		char c = text[i];
		if (c == '\n')
		{
			yi += fontHeight;
			xi = x;
			continue;
		}

		c -= 32;
		float bottom = yi + fontHeight, top = yi, left = xi, right = xi + fontWidth;
		float u0 = (c % 16) * uStep, u1 = u0 + uStep,
			  v0 = (c / 16) * vStep, v1 = v0 + vStep;

		vertices.push_back(VertexFont(left, bottom, u0, v1));
		vertices.push_back(VertexFont(left, top, u0, v0));
		vertices.push_back(VertexFont(right, bottom, u1, v1));
		
		vertices.push_back(VertexFont(right, bottom, u1, v1));
		vertices.push_back(VertexFont(left, top, u0, v0));
		vertices.push_back(VertexFont(right, top, u1, v0));
		
		xi += fontWidth;
	}
	m_fontShape.setVertexBuffer((float*)&vertices[0], vertices.size(), 4);

	m_fontShader.apply();
	m_fontShape.draw();
}
//--------------------------------------------------------------------