#ifndef BASICVERTEX_H
#define BASICVERTEX_H

#include "../glsdk/glm/glm/glm.hpp"

class RubiksCubeVertex
{
public:
	glm::vec3 position;
	glm::vec4 color;
	glm::vec3 normal; //glm::vec3 lieg im Speicher genau so wie float normal[3] und kann auch genau so angesprochen werden, weil glm::vec3 den []-Operator überschreibt.
	glm::vec3 tangent;
	glm::vec3 binormal;
	glm::vec2 uv; //Texturkoordinaten.

	RubiksCubeVertex();
	void setPosition(float x, float y, float z);
	void setColor(float r, float g, float b, float a);
	void setUV(float u, float v);
	void print();
};

#endif // BASICVERTEX_H
