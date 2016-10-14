#include "Cube.h"
#include "Utilities/Debug.h"
//--------------------------------------------------------------------

bool Cube::generateCube(float size, bool inverseNormal, bool reverseTexture)
{
	float half = size / 2.0f;
	float normal = (inverseNormal) ? -1.0f : 1.0f;
	float texZero = (reverseTexture) ? 1.0f : 0.0f;
	float texOne = (reverseTexture) ? 0.0f : 1.0f;

	float vertices[] =
    { 
		//	Front
        -half, -half, -half,	0.0f, 0.0f, -normal,	0.0f, texZero,
        -half, half, -half,		0.0f, 0.0f, -normal,	0.0f, texOne,
        half, -half, -half,		0.0f, 0.0f, -normal,	1.0f, texZero,
		
        half, -half, -half,		0.0f, 0.0f, -normal,	1.0f, texZero,
        -half, half, -half,		0.0f, 0.0f, -normal,	0.0f, texOne,
        half, half, -half,		0.0f, 0.0f, -normal,	1.0f, texOne,
		
		//	Back
        half, -half, half,		0.0f, 0.0f, normal,		0.0f, texZero,
        half, half, half,		0.0f, 0.0f, normal,		0.0f, texOne,
        -half, -half, half,		0.0f, 0.0f, normal,		1.0f, texZero,
		
        -half, -half, half,		0.0f, 0.0f, normal,		1.0f, texZero,
        half, half, half,		0.0f, 0.0f, normal,		0.0f, texOne,
        -half, half, half,		0.0f, 0.0f, normal,		1.0f, texOne,

		//	Left
        half, -half, -half,		normal, 0.0f, 0.0f,		0.0f, texZero,
        half, half, -half,		normal, 0.0f, 0.0f,		0.0f, texOne,
        half, -half, half,		normal, 0.0f, 0.0f,		1.0f, texZero,
		
        half, -half, half,		normal, 0.0f, 0.0f,		1.0f, texZero,
        half, half, -half,		normal, 0.0f, 0.0f,		0.0f, texOne,
        half, half, half,		normal, 0.0f, 0.0f,		1.0f, texOne,

		//	Right
        -half, -half, half,		-normal, 0.0f, 0.0f,	0.0f, texZero,
        -half, half, half,		-normal, 0.0f, 0.0f,	0.0f, texOne,
        -half, -half, -half,	-normal, 0.0f, 0.0f,	1.0f, texZero,
		
        -half, -half, -half,	-normal, 0.0f, 0.0f,	1.0f, texZero,
        -half, half, half,		-normal, 0.0f, 0.0f,	0.0f, texOne,
        -half, half, -half,		-normal, 0.0f, 0.0f,	1.0f, texOne,

		//	Top
        -half, half, -half,		0.0f, normal, 0.0f,		0.0f, texZero,
        -half, half, half,		0.0f, normal, 0.0f,		0.0f, texOne,
        half, half, -half,		0.0f, normal, 0.0f,		1.0f, texZero,
		
        half, half, -half,		0.0f, normal, 0.0f,		1.0f, texZero,
        -half, half, half,		0.0f, normal, 0.0f,		0.0f, texOne,
        half, half, half,		0.0f, normal, 0.0f,		1.0f, texOne,

		//	Bottom
        half, -half, -half,		0.0f, -normal, 0.0f,	1.0f, texZero,
        -half, -half, half,		0.0f, -normal, 0.0f,	0.0f, texOne,
        -half, -half, -half,	0.0f, -normal, 0.0f,	0.0f, texZero,
		
        half, -half, half,		0.0f, -normal, 0.0f,	1.0f, texOne,
        -half, -half, half,		0.0f, -normal, 0.0f,	0.0f, texOne,
        half, -half, -half,		0.0f, -normal, 0.0f,	1.0f, texZero,
    };

	if (!loadVertexBuffer(vertices, 36, true, true))
	{
		outputMsg("Failed to create cube\n");
		return false;
	}
	return true;
}
//--------------------------------------------------------------------

bool Cube::generateCubeVertexOnly(float size)
{
	float half = size / 2.0f;

	float vertices[] =
    { 
		//	Front
        -half, -half, -half,
        -half, half, -half,
        half, -half, -half,
		
        half, -half, -half,
        -half, half, -half,
        half, half, -half,
		
		//	Back
        half, -half, half,
        -half, half, half,
        -half, -half, half,
		
        half, half, half,
        -half, half, half,
        half, -half, half,

		//	Right
        half, -half, -half,
        half, half, -half,
        half, -half, half,
		
        half, -half, half,
        half, half, -half,
        half, half, half,

		//	Left
        -half, -half, half,
        -half, half, -half,
        -half, -half, -half,
		
        -half, half, half,
        -half, half, -half,
        -half, -half, half,

		//	Top
        -half, half, -half,
        -half, half, half,
        half, half, -half,
		
        half, half, -half,
        -half, half, half,
        half, half, half,

		//	Bottom
        half, -half, -half,
        -half, -half, half,
        -half, -half, -half,
		
        half, -half, half,
        -half, -half, half,
        half, -half, -half,
    };

	if (!loadVertexBuffer(vertices, 36, 3))
	{
		outputMsg("Failed to create cube\n");
		return false;
	}
	return true;
}
//--------------------------------------------------------------------