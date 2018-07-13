#ifndef RUBICSCUBEMESH_H
#define RUBICSCUBEMESH_H

#include "Cube.h"

class RubiksCubeDataModel;

class RubiksCubeMesh
{
public:
	RubiksCubeMesh(float size);
	Cube cube[3][3][3];

	void updateColors(RubiksCubeDataModel& dataModel);
};

#endif // RUBICSCUBEMESH_H
