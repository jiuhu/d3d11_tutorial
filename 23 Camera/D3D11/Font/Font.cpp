#include "Font.h"
#include "Graphics/Shapes/Shapes.h"
#include <vector>
#include "D3D11/DxDevices.h"
//--------------------------------------------------------------------

const float fontWidth = 16.0f,
			fontHeight = 20.0f,
			uStep = fontWidth / 256.0f, 
			vHeight = fontHeight / 256.0f,
			vStep = 32.0f / 256.0f;
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
	m_fontFace.loadTexture2DFromFile(fontFileName.c_str());
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

		const TexCoordFont * t = DxDevices::_fontList.getTexCoord(c);

		vertices.push_back(VertexFont(Vertex2(left, bottom), t->_t[0]));
		vertices.push_back(VertexFont(Vertex2(left, top), t->_t[1]));
		vertices.push_back(VertexFont(Vertex2(right, bottom), t->_t[2]));
		vertices.push_back(VertexFont(Vertex2(right, top), t->_t[3]));
		
		xi += fontWidth;
	}
	m_fontShape.loadVertexBuffer((float*)&vertices[0], vertices.size(), 4, D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_fontShader.apply();
	m_fontFace.apply(0);
	m_fontShape.draw();
}
//--------------------------------------------------------------------

void Font::drawFormattedText(float x, float y, const char * const format, ...)
{
	va_list args;
	va_start(args, format);
	int size = _vscprintf(format, args) + 1;
	char * strBuffer = new char[size];
	vsprintf_s(strBuffer, size, format, args);
	va_end(args);

	drawText(x, y, strBuffer);
	delete [] strBuffer;
}
//--------------------------------------------------------------------