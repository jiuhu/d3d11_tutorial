#pragma once

#include <vector>
#include <fstream>
#include <string>
#include "Utilities/Math/Vector2f.h"
#include "Utilities/Math/Vector3f.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

using namespace std;
//--------------------------------------------------------------------

bool loadOBJFileToVertexArray(const char * const objFile, float scale, bool inverseTexture,
							  _Out_ vector<float> &vertexArray) 
{
	ifstream fin(objFile);
	if(!fin)
	{
		outputMsg("Read file %s failed\n", objFile);
		return false;
	}

	vector<Vector3f> vertex;
	vector<Vector2f> texture;
	vector<Vector3f> normal;
	vector<unsigned int> vIndex;
	vector<unsigned int> tIndex;
	vector<unsigned int> nIndex;

	string attribute;

	// put them out to reduce some initiate time
	Vector3f v;
	Vector2f t;
	Vector3f n;
	unsigned int in[3];
	char divider;

	while(fin >> attribute)
	{
		// read the vertices
		if (attribute.compare("v") == 0)
		{
			fin >> v.x >> v.y >> v.z;
			v *= scale;
			vertex.push_back(v);
		}
		// read the textures coordinate
		else if(attribute.compare("vt") == 0)
		{
			fin >> t.x >> t.y; 
			if (inverseTexture) 
			{
				t.x = 1.0f - t.x;
				t.y = 1.0f - t.y;
			}
			texture.push_back(t);
		}
		// read the normals
		else if (attribute.compare("vn") == 0)
		{
			fin >> n.x >> n.y >> n.z;
			normal.push_back(n);
		}
		// read the faces
		else if (attribute.compare("f") == 0)
		{
			fin >> in[0] >> divider >> in[1] >> divider >> in[2];
			vIndex.push_back(--in[0]);
			tIndex.push_back(--in[1]);
			nIndex.push_back(--in[2]);

			fin >> in[0] >> divider >> in[1] >> divider >> in[2];
			vIndex.push_back(--in[0]);
			tIndex.push_back(--in[1]);
			nIndex.push_back(--in[2]);

			fin >> in[0] >> divider >> in[1] >> divider >> in[2];
			vIndex.push_back(--in[0]);
			tIndex.push_back(--in[1]);
			nIndex.push_back(--in[2]);
		}
	}

	UINT vertexCount = 0;
	for (UINT i = 0; i < vIndex.size(); i++) {
		vertexArray.push_back(vertex[vIndex[i]].x);
		vertexArray.push_back(vertex[vIndex[i]].y);
		vertexArray.push_back(vertex[vIndex[i]].z);

		vertexArray.push_back(normal[nIndex[i]].x);
		vertexArray.push_back(normal[nIndex[i]].y);
		vertexArray.push_back(normal[nIndex[i]].z);

		vertexArray.push_back(texture[tIndex[i]].x);
		vertexArray.push_back(texture[tIndex[i]].y);
	}

	return true;
}
//--------------------------------------------------------------------