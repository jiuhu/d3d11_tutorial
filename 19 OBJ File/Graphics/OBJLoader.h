#pragma once

#include <vector>
//--------------------------------------------------------------------

bool loadOBJFileToVertexArray(const char * const objFile, float scale, bool inverseTexture,
									 _Out_ std::vector<float> &vertexArray);
//--------------------------------------------------------------------