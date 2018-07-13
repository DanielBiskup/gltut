#include "BasicVertex.h"
#include <iostream>

RubiksCubeVertex::RubiksCubeVertex()
{
	setPosition(0.0f,0.0f,0.0f);
	setColor(1.0f, 0.0f, 0.0f, 1.0f);
}

void RubiksCubeVertex::setPosition(float x, float y, float z)
{
	position[0] = x;
	position[1] = y;
	position[2] = z;
}

void RubiksCubeVertex::setColor(float r, float g, float b, float a)
{
	color[0] = r;
	color[1] = g;
	color[2] = b;
	color[3] = a;
}

void RubiksCubeVertex::setUV(float u, float v)
{
	uv.x = u;
	uv.y = v;
}



void RubiksCubeVertex::print()
{
	std::cout << "X: " << position[0] << ",\t Y: " << position[1] << ",\t Z:" << position[2] << std::endl;
}
