#pragma once

#include <vector>
//--------------------------------------------------------------------

class TexCoordFont;
//--------------------------------------------------------------------

class FontList
{
public:

	FontList();

	~FontList();

	const TexCoordFont * getTexCoord(int index) const
	{
		return m_texCoords[index];
	}

private:
	
	std::vector<TexCoordFont *> m_texCoords;
};
//--------------------------------------------------------------------