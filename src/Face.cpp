#include "Face.h"
#include "../glsdk/glm/glm/glm.hpp"
#include <iostream>

Face::Face()
{
	setColor(1.0f,1.0f,0.0f,1.0f);
}

void Face::setVertexPosition(glm::core::type::vec3 p0, glm::core::type::vec3 p1, glm::core::type::vec3 p2, glm::core::type::vec3 p3)
{
	vertices[0].position = vertices[3].position = p0;	//p0
	vertices[4].position = p1;							//p1
	vertices[1].position = vertices[5].position = p2;	//p2
	vertices[2].position = p3;							//p3

	//this->updateNormals();
	calculateNormalTangentAndBinormal(p0, p1, p3);
	this->updateUvCoordinates();
}

void Face::setColor(float r, float g, float b, float a)
{
	for(int i=0;i<6;i++)
	{
		float f = 1.0 - 0.1*i;
		vertices[i].setColor(r*f,g*f,b*f,a);
		vertices[i].setColor(r,g,b,a);
	}
}

void Face::setColorByColorId(int colorId)
{
	float r = 0;
	float g = 0;
	float b = 0;
	switch(colorId)
	{
	case 0:
		r = 1;
		break;
	case 1:
		g = 1;
		break;
	case 2:
		b = 1;
		break;
	case 3:
		r=g=b=1;
		break;
	case 4:
		r=0.5;
		b=1;
		break;
	case 5:
		r=b=1;
		break;
	}

	std::cout << " r: " << r << " g: " << g << " b: " << b << std::endl;
	setColor(r,g,b,1);
}

//void Face::updateNormals()
//{
//	glm::vec3 p0(vertices[0].position);
//	glm::vec3 p1(vertices[1].position);
//	glm::vec3 p2(vertices[2].position);
//	glm::vec3 normal( glm::cross((p1 - p0), (p2-p0)));
//	normal = glm::normalize(normal);

//	for(int i=0;i<6;i++)
//		vertices[i].normal = normal;
//}

void Face::calculateNormalTangentAndBinormal(glm::core::type::vec3 p0, glm::core::type::vec3 p1, glm::core::type::vec3 p3)
{
	glm::vec3 tangent(glm::normalize(p1 - p0));
	glm::vec3 binormal(glm::normalize(p3 - p0));
	glm::vec3 normal(glm::normalize(glm::cross(tangent,binormal)));

	for(int i=0;i<6;i++)
	{
		vertices[i].normal = normal;
		vertices[i].tangent = tangent;
		vertices[i].binormal = binormal;
	}
}

void Face::updateUvCoordinates()
{
	vertices[0].uv = vertices[3].uv = glm::vec2(0,0);;	//p0
	vertices[4].uv = glm::vec2(1,0);					//p1
	vertices[1].uv = vertices[5].uv = glm::vec2(1,1);	//p2
	vertices[2].uv = glm::vec2(0,1);					//p3
}
