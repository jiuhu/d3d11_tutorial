//--------------------------------------------------------------------
//
//	Font.h
//
//	Ewe Yee Seong
//	MSc Games Programming, 2009 - 2010
//	University of Hull
//


#include "Font.h"
#include <stdio.h>
//--------------------------------------------------------------------

Font::Font()
	:	m_renderTarget(nullptr),
		m_textFormat(nullptr),
		m_brush(nullptr)
{
}
//--------------------------------------------------------------------

Font::~Font()
{
	if (m_textFormat)
	{
		m_textFormat->Release();
		m_textFormat = nullptr;
	}
	
	if (m_brush)
	{
		m_brush->Release();
		m_brush = nullptr;
	}

	m_renderTarget = nullptr;
}
//--------------------------------------------------------------------

HRESULT Font::init(IDWriteFactory * writeFactory, ID2D1RenderTarget * renderTarget, 
				const WCHAR * const family, float size)
{
	return init(writeFactory, renderTarget, family, size, 
				DWRITE_FONT_WEIGHT_REGULAR, DWRITE_FONT_STYLE_NORMAL, 
				D2D1::ColorF(1.0f, 1.0f, 1.0f, 1.0f));
}
//--------------------------------------------------------------------

HRESULT Font::init(IDWriteFactory * writeFactory, ID2D1RenderTarget * renderTarget, 
				const WCHAR * const family, float size, 
				DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, 
				CONST D2D1_COLOR_F &color)
{
	m_renderTarget = renderTarget;
	
	m_fontSize = size;

	HRESULT hr = writeFactory->CreateTextFormat(family, NULL, weight, style,
												DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", &m_textFormat);
	if(FAILED(hr))
		return hr;

	hr = m_renderTarget->CreateSolidColorBrush(color, &m_brush);
	if(FAILED(hr))
		return hr;
	
	return hr;
}
//--------------------------------------------------------------------

void Font::drawFormattedText(float x, float y, const WCHAR * const format, ...) const
{
	va_list args;
	va_start(args, format);
	int size = _vscwprintf(format, args) + 1;
	WCHAR * strBuffer = new WCHAR[size];
	vswprintf_s(strBuffer, size, format, args);
	va_end(args);
	
	drawText(x, y, strBuffer, size);
	delete [] strBuffer;
}
//--------------------------------------------------------------------