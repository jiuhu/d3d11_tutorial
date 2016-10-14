#include "FontList.h"
#include "Graphics/Shapes/Shapes.h"
#include "Utilities/Helper.h"
//--------------------------------------------------------------------

FontList::FontList()
{
	int characterCount = 97;
	m_texCoords.reserve(characterCount);

	const float FontWidth = 16.0f,
				FontHeight = 32.0f,
				FontListHeight = 20.0f,
				uStep = FontWidth / 256.0f, 
				vHeight = FontListHeight / 256.0f,
				vStep = FontHeight / 256.0f;
	
	for (int i = 0; i < characterCount; ++i)
	{
		float u0 = (i % 16) * uStep, u1 = u0 + uStep,
			  v0 = (i / 16) * vStep, v1 = v0 + vHeight;

		m_texCoords.push_back(new TexCoordFont(TexCoord(u0, v1), TexCoord(u0, v0), TexCoord(u1, v1), TexCoord(u1, v0)));
	}
}
//--------------------------------------------------------------------

FontList::~FontList()
{
	deallocateVector(m_texCoords);
}
//--------------------------------------------------------------------