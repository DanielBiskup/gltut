#ifndef CUBE_H
#define CUBE_H

#include "Face.h"

class Cube
{
public:
	Cube();
	Face face[6];

	void adjustPositionAndSize(float x, float y, float z, float size);

	//not needed in final release:
	void setColorForCube(float r, float g, float b, float a);

};

#endif // CUBE_H
