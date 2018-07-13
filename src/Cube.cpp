#include "Cube.h"

void Cube::adjustPositionAndSize(float x, float y, float z, float size)
{
	float a = size/2.f;

	//VertexPositions direkt über setVertexPositions setzen:
	//Die 8 Punkte des Würfels berechnen:
	glm::vec3 p0(x+a,y-a,z+a);
	glm::vec3 p1(x+a,y-a,z-a);
	glm::vec3 p2(x+a,y+a,z-a);
	glm::vec3 p3(x+a,y+a,z+a);
	glm::vec3 p4(x-a,y-a,z+a);
	glm::vec3 p5(x-a,y-a,z-a);
	glm::vec3 p6(x-a,y+a,z-a);
	glm::vec3 p7(x-a,y+a,z+a);

	face[0].setVertexPosition(p4, p0, p3, p7);
	face[1].setVertexPosition(p0, p1, p2, p3);
	face[2].setVertexPosition(p1, p5, p6, p2);
	face[3].setVertexPosition(p5, p4, p7, p6);
	face[4].setVertexPosition(p7, p3, p2, p6);
	face[5].setVertexPosition(p5, p1, p0, p4);
}

Cube::Cube()
{
	adjustPositionAndSize(0.f,0.f,0.f,0.5f);
}

void Cube::setColorForCube(float r, float g, float b, float a)
{
	for(int i=0;i<6;i++)
	{
		face[i].setColor(r,g,b,a);
	}
}
