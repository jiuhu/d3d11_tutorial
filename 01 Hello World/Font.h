//--------------------------------------------------------------------
//
//	Font.h
//
//	Ewe Yee Seong
//	MSc Games Programming, 2009 - 2010
//	University of Hull
//


/**	Revision History

		Rev 1.0		04 Nov 2012		Define DirectWrite for font

*/


#pragma once

#include <d2d1.h>
#include <dwrite.h>
//--------------------------------------------------------------------

class Font 
{
public:

	/*
		Constructor.
	*/
	Font();

	/*
		Destructor.
	*/
	~Font();

	/*
		This function will initialize default font.
		Default font = Normal weight, normal style, white color
	*/
	HRESULT init(IDWriteFactory * writeFactory, ID2D1RenderTarget * renderTarget, 
				const WCHAR * const family, float size);

	/*
		This function will initialize customize font.
		Default font = Normal weight, normal style, white color
	*/
	HRESULT init(IDWriteFactory * writeFactory, ID2D1RenderTarget * renderTarget, 
				const WCHAR * const family, float size, 
				DWRITE_FONT_WEIGHT weight, DWRITE_FONT_STYLE style, 
				CONST D2D1_COLOR_F &color);

	/*
		This function is called to print out a formatted text on screen.
	*/
	void drawFormattedText(float x, float y, const WCHAR * const format, ...) const;

	/*
		This function is called to print out a plain text.
	*/
	void drawText(float x, float y, const WCHAR * const text) const;

	/*
		This function is called to print out a plain text.
	*/
	void drawText(float x, float y, const WCHAR * const text, int size) const;

private:

	//	Pointer to the render target.
	ID2D1RenderTarget * m_renderTarget;

	//	Pointer to the text format.
	IDWriteTextFormat * m_textFormat;

	//	Pointer to the brush.
	ID2D1SolidColorBrush * m_brush;

	//	Font size.
	float m_fontSize;
};
//--------------------------------------------------------------------

inline void Font::drawText(float x, float y, const WCHAR * const text) const
{
	drawText(x, y, text, wcslen(text));
}
//--------------------------------------------------------------------

inline void Font::drawText(float x, float y, const WCHAR * const text, int size) const
{
	m_renderTarget->DrawText(text, size, m_textFormat, 
							 D2D1::RectF(x, y, x + (size * m_fontSize), y + m_fontSize),
							 m_brush);
}
//--------------------------------------------------------------------
