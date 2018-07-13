#include "RubiksCubeMesh.h"
#include "RubiksCubeDataModel.h"

Cube cube[3][3][3];
RubiksCubeMesh::RubiksCubeMesh(float size)
{
	float cubeSize = size/3.f;
	for(int x=0; x<3; x++)
	{
		for(int y=0; y<3; y++)
		{
			for(int z=0; z<3; z++)
			{
				float x_pos = (-1 + x) * cubeSize;
				float y_pos = (-1 + y) * cubeSize;
				float z_pos = (-1 + z) * -1 * cubeSize;
				cube[x][y][z].adjustPositionAndSize(x_pos, y_pos, z_pos, cubeSize);
			}
		}
	}
}

void RubiksCubeMesh::updateColors(RubiksCubeDataModel& dataModel)
{
	int x;
	int y;
	int z;
	int face;

	//RubiksCube Face 0:
	face=0;
	z=0;
	for (x=0; x<3; x++)
		for (y=0; y<3; y++)
					cube[x][y][z].face[face].setColorByColorId(dataModel.getColorAt(face,x,y));

	//RubiksCube Face 1:
	face=1;
	x=2;
	for (y=0; y<3; y++)
		for (z=0; z<3; z++)
					cube[x][y][z].face[face].setColorByColorId(dataModel.getColorAt(face,z,y));

	//RubiksCube Face 2:
	face=2;
	z=2;
	for (x=0; x<3; x++)
		for (y=0; y<3; y++)
					cube[x][y][z].face[face].setColorByColorId(dataModel.getColorAt(face,2-x,y));

	//RubiksCube Face 3:
	face=3;
	x=0;
	for (y=0; y<3; y++)
		for (z=0; z<3; z++)
					cube[x][y][z].face[face].setColorByColorId(dataModel.getColorAt(face,2-z,y));

	//RubiksCube Face 4:
	face=4;
	y=2;
	for (x=0; x<3; x++)
		for (z=0; z<3; z++)
					cube[x][y][z].face[face].setColorByColorId(dataModel.getColorAt(face, x, z));

	//RubiksCube Face 5:
	face=5;
	y=0;
	for (x=0; x<3; x++)
		for (z=0; z<3; z++)
					cube[x][y][z].face[face].setColorByColorId(dataModel.getColorAt(face, x, 2-z));

}
